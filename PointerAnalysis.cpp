#include "PointerAnalysis.h"

#include <boost/filesystem.hpp>
#include <boost/flyweight.hpp>
#include <unordered_set>

#include "PAInterface.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Support/CommandLine.h"

// Legacy pass manager
#include "llvm/Pass.h"

// New pass manager
#include "ContextSensitivity.hpp"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "wrapper.hpp"

namespace fs = boost::filesystem;

enum class Analysis {
  DEBUG,
  SUBSET_AND_UNIFICATION,
  SUBSET,
  UNIFICATION,
};

namespace cclyzer {
llvm::cl::opt<Analysis> datalog_analysis(
    "datalog-analysis",
    llvm::cl::desc("Which pointer analysis to variant run"),
    llvm::cl::values(
        clEnumValN(Analysis::DEBUG, "debug", "debug (both)"),
        clEnumValN(
            Analysis::SUBSET_AND_UNIFICATION, "subset-and-unification", "both"),
        clEnumValN(Analysis::SUBSET, "subset", "subset analysis only"),
        clEnumValN(
            Analysis::UNIFICATION,
            "unification",
            "unification analysis only")));

llvm::cl::opt<bool> datalog_debug_option(
    "debug-datalog",
    llvm::cl::desc("Keep intermediate files generated by datalog"),
    llvm::cl::init(false));

llvm::cl::opt<std::string> datalog_debug_dir_option(
    "debug-datalog-dir",
    llvm::cl::desc("Where to keep intermediate files generated by datalog"),
    llvm::cl::init((fs::temp_directory_path() / fs::unique_path()).native()));

llvm::cl::opt<bool> datalog_check_assertions_option(
    "check-datalog-assertions",
    llvm::cl::desc("Check assertions in the datalog code"),
    llvm::cl::init(false));

llvm::cl::opt<std::string> signatures(
    "signatures", llvm::cl::desc("File with points-to signatures"));

llvm::cl::opt<ContextSensitivity> context_sensitivity(
    "context-sensitivity",
    llvm::cl::desc("Set the context sensitivity of the pointer analysis"),
    llvm::cl::values(
        clEnumValN(INSENSITIVE, INSENSITIVE_STRING, "context insensitive"),
        clEnumValN(CALLSITE1, CALLSITE1_STRING, "depth 1 callsite sensitive"),
        clEnumValN(CALLSITE2, CALLSITE2_STRING, "depth 2 callsite sensitive"),
        clEnumValN(CALLSITE3, CALLSITE3_STRING, "depth 3 callsite sensitive"),
        clEnumValN(CALLSITE4, CALLSITE4_STRING, "depth 4 callsite sensitive"),
        clEnumValN(CALLSITE5, CALLSITE5_STRING, "depth 5 callsite sensitive"),
        clEnumValN(CALLSITE6, CALLSITE6_STRING, "depth 6 callsite sensitive"),
        clEnumValN(CALLSITE7, CALLSITE7_STRING, "depth 7 callsite sensitive"),
        clEnumValN(CALLSITE8, CALLSITE8_STRING, "depth 8 callsite sensitive"),
        clEnumValN(CALLSITE9, CALLSITE9_STRING, "depth 9 callsite sensitive"),
        clEnumValN(CALLER1, CALLER1_STRING, "depth 1 caller sensitive"),
        clEnumValN(CALLER2, CALLER2_STRING, "depth 2 caller sensitive"),
        clEnumValN(CALLER3, CALLER3_STRING, "depth 3 caller sensitive"),
        clEnumValN(CALLER4, CALLER4_STRING, "depth 4 caller sensitive"),
        clEnumValN(CALLER5, CALLER5_STRING, "depth 5 caller sensitive"),
        clEnumValN(CALLER6, CALLER6_STRING, "depth 6 caller sensitive"),
        clEnumValN(CALLER7, CALLER7_STRING, "depth 7 caller sensitive"),
        clEnumValN(CALLER8, CALLER8_STRING, "depth 8 caller sensitive"),
        clEnumValN(CALLER9, CALLER9_STRING, "depth 9 caller sensitive"),
        clEnumValN(FILE1, FILE1_STRING, "depth 1 file sensitive"),
        clEnumValN(FILE2, FILE2_STRING, "depth 2 file sensitive"),
        clEnumValN(FILE3, FILE3_STRING, "depth 3 file sensitive"),
        clEnumValN(FILE4, FILE4_STRING, "depth 4 file sensitive"),
        clEnumValN(FILE5, FILE5_STRING, "depth 5 file sensitive"),
        clEnumValN(FILE6, FILE6_STRING, "depth 6 file sensitive"),
        clEnumValN(FILE7, FILE7_STRING, "depth 7 file sensitive"),
        clEnumValN(FILE8, FILE8_STRING, "depth 8 file sensitive"),
        clEnumValN(FILE9, FILE9_STRING, "depth 9 file sensitive")));

auto PointerAnalysisAAResult::alias(
    const llvm::MemoryLocation &location,
    const llvm::MemoryLocation &other_location,
    llvm::AAQueryInfo &AAQI) -> llvm::AliasResult {
  if (location.Ptr == other_location.Ptr) {
    return llvm::MustAlias;
  }

  std::unordered_set<boost::flyweight<std::string>> points_to_set;
  std::unordered_set<boost::flyweight<std::string>> other_points_to_set;
  for (const auto &tuple : variable_points_to_) {
    const auto &to = std::get<1>(tuple);
    const auto from = std::get<3>(tuple);
    if (from == location.Ptr) {
      if (other_points_to_set.find(to) != other_points_to_set.end()) {
        return AAResultBase::alias(location, other_location, AAQI);
      }

      points_to_set.insert(to);
    }

    if (from == other_location.Ptr) {
      if (points_to_set.find(to) != points_to_set.end()) {
        return AAResultBase::alias(location, other_location, AAQI);
      }

      other_points_to_set.insert(to);
    }
  }

  return llvm::NoAlias;
}

static auto get_interface(Analysis which) -> std::unique_ptr<PAInterface> {
  switch (which) {
    case Analysis::DEBUG:
      return PAInterface::create("debug");
    case Analysis::SUBSET_AND_UNIFICATION:
      return PAInterface::create("subset_and_unification");
    case Analysis::SUBSET:
      return PAInterface::create("subset");
    case Analysis::UNIFICATION:
      return PAInterface::create("unification");
  }
  assert(false && "unreachable");
}

static auto callgraph_edge(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset.callgraph.callgraph_edge";
    case Analysis::UNIFICATION:
      return "unification.callgraph.callgraph_edge";
  }
  assert(false && "unreachable");
}

static auto alloc_may_alias(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset_lift.alloc_may_alias_ctx";
    case Analysis::UNIFICATION:
      return "unification_lift.alloc_may_alias_ctx";
  }
  assert(false && "unreachable");
}

static auto alloc_must_alias(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset_lift.alloc_must_alias_ctx";
    case Analysis::UNIFICATION:
      return "unification_lift.alloc_must_alias_ctx";
  }
  assert(false && "unreachable");
}

static auto alloc_subregion(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset_lift.alloc_subregion_ctx";
    case Analysis::UNIFICATION:
      return "unification_lift.alloc_subregion_ctx";
  }
  assert(false && "unreachable");
}

static auto alloc_contains(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset_lift.alloc_contains_ctx";
    case Analysis::UNIFICATION:
      return "unification_lift.alloc_contains_ctx";
  }
  assert(false && "unreachable");
}

static auto ptr_points_to(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset.ptr_points_to";
    case Analysis::UNIFICATION:
      return "unification.ptr_points_to_final";
  }
  assert(false && "unreachable");
}

static auto operand_points_to(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset.operand_points_to";
    case Analysis::UNIFICATION:
      return "unification.operand_points_to_final";
  }
  assert(false && "unreachable");
}

static auto var_points_to(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset.var_points_to";
    case Analysis::UNIFICATION:
      return "unification.var_points_to_final";
  }
  assert(false && "unreachable");
}

static auto allocation_size(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset_lift.allocation_size_ctx";
    case Analysis::UNIFICATION:
      return "unification_lift.allocation_size_ctx";
  }
  assert(false && "unreachable");
}

static auto allocation_by_instruction(Analysis which) -> std::string {
  switch (which) {
    case Analysis::DEBUG:
      [[fallthrough]];
    case Analysis::SUBSET_AND_UNIFICATION:
      [[fallthrough]];
    case Analysis::SUBSET:
      return "subset_lift.allocation_by_instruction_ctx";
    case Analysis::UNIFICATION:
      return "unification_lift.allocation_by_instruction_ctx";
  }
  assert(false && "unreachable");
}

auto LegacyPointerAnalysis::runOnModule(llvm::Module &mod) -> bool {
  const fs::path output_dir = fs::path(datalog_debug_dir_option);
  if (!fs::exists(output_dir)) {
    fs::create_directories(output_dir);
  }

  llvm::Optional<fs::path> signatures_path;
  if (signatures != "") {
    signatures_path = llvm::Optional<fs::path>(fs::path(signatures));
  } else {
    signatures_path = llvm::Optional<fs::path>();
  }

  auto [dir, llvm_val_map] =
      factgen_module(mod, output_dir, signatures_path, context_sensitivity);
  const auto pa = get_interface(datalog_analysis);
  PAFlags flags = PAFlags::NONE;
  if (datalog_debug_option) {
    flags = flags | PAFlags::WRITE_ALL;
  }

  pa->runPointerAnalysis(dir, flags, llvm_val_map);
  if (datalog_check_assertions_option) {
    pa->checkAssertions(datalog_analysis == Analysis::DEBUG);
  }

  std::map<int, boost::flyweight<std::string>> context_to_string;
  const auto context_to_string_vec =
      pa->relationToVector<int, boost::flyweight<std::string>>(
          "context_to_string", llvm_val_map);
  for (const auto &[fst, snd] : context_to_string_vec) {
    context_to_string.emplace(fst, snd);
  }

  std::multimap<const llvm::Value *, std::tuple<int, int, const llvm::Value *>>
      call_graph;
  const auto callgraph_vec =
      pa->relationToVector<int, const llvm::Value *, int, const llvm::Value *>(
          callgraph_edge(datalog_analysis), llvm_val_map);
  for (const auto &[callee_ctx, callee, caller_ctx, caller] : callgraph_vec) {
    std::tuple<int, int, const llvm::Value *> entry(
        caller_ctx, callee_ctx, callee);
    call_graph.emplace(caller, entry);
  }

  std::set<const llvm::Value *> null_ptr_set;
  auto var_points_to_rel = pa->relationToVector<
      int,
      boost::flyweight<std::string>,
      int,
      const llvm::Value *>(var_points_to(datalog_analysis), llvm_val_map);
  for (const auto &[_alloc_ctx, alias_set_identifier, _pointer_ctx, value] :
       var_points_to_rel) {
    // *null* is the null_location in the Datalog code.
    if (alias_set_identifier == "*null*") {
      null_ptr_set.emplace(value);
    }
  }

  result_ = std::make_unique<PointerAnalysisAAResult>(
      std::move(context_to_string),
      std::move(var_points_to_rel),
      pa->relationToVector<
          int,
          boost::flyweight<std::string>,
          boost::flyweight<std::string>>(
          alloc_may_alias(datalog_analysis), llvm_val_map),
      pa->relationToVector<
          int,
          boost::flyweight<std::string>,
          boost::flyweight<std::string>>(
          alloc_must_alias(datalog_analysis), llvm_val_map),
      pa->relationToVector<
          int,
          boost::flyweight<std::string>,
          boost::flyweight<std::string>>(
          alloc_subregion(datalog_analysis), llvm_val_map),
      pa->relationToVector<
          int,
          boost::flyweight<std::string>,
          boost::flyweight<std::string>>(
          alloc_contains(datalog_analysis), llvm_val_map),
      pa->relationToVector<
          int,
          boost::flyweight<std::string>,
          int,
          boost::flyweight<std::string>>(
          ptr_points_to(datalog_analysis), llvm_val_map),
      pa->relationToVector<
          int,
          boost::flyweight<std::string>,
          int,
          const llvm::Value *>(
          operand_points_to(datalog_analysis), llvm_val_map),
      pa->relationToVector<const llvm::Value *, boost::flyweight<std::string>>(
          "global_allocation_by_variable", llvm_val_map),
      pa->relationToVector<int, boost::flyweight<std::string>, int>(
          allocation_size(datalog_analysis), llvm_val_map),
      pa->relationToVector<
          int,
          const llvm::Value *,
          int,
          boost::flyweight<std::string>>(
          allocation_by_instruction(datalog_analysis), llvm_val_map),
      std::move(null_ptr_set),
      std::move(call_graph));
  if (!datalog_debug_option) {
    boost::filesystem::remove_all(dir);
  }
  return false;
}

auto PointerAnalysis::run(llvm::Module &module, llvm::ModuleAnalysisManager &)
    -> PointerAnalysis::Result {
  LegacyPointerAnalysis legacy_pa;
  legacy_pa.runOnModule(module);
  return legacy_pa.getResult();
}

// Modern pass manager registration

llvm::AnalysisKey PointerAnalysis::Key;

extern "C" LLVM_ATTRIBUTE_WEAK auto llvmGetPassPluginInfo()
    -> ::llvm::PassPluginLibraryInfo {
  return {
      LLVM_PLUGIN_API_VERSION, "cclyzer", "v0.1", [](llvm::PassBuilder &pb) {
        pb.registerAnalysisRegistrationCallback(
            [](llvm::ModuleAnalysisManager &module_analysis_manager) {
              module_analysis_manager.registerPass(
                  [&] { return PointerAnalysis(); });
            });
      }};
}

// Legacy pass manager registration

char LegacyPointerAnalysis::ID = 0;
static llvm::RegisterPass<LegacyPointerAnalysis> X(
    "cclyzer", "Pointer Analysis Pass", false, true);
}  // namespace cclyzer
