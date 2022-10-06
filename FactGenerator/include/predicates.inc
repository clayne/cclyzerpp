// Default to empty definitions
#ifndef GROUP_BEGIN
#define GROUP_BEGIN(group)
#endif
#ifndef GROUP_END
#define GROUP_BEGIN(group)
#endif
#ifndef PREDICATE
#define PREDICATE(group, name)
#endif

GROUP_BEGIN(basic_block)
PREDICATE(basic_block, predecessor)
GROUP_END(basic_block)

GROUP_BEGIN(global_var)
PREDICATE(global_var, id)
PREDICATE(global_var, name)
PREDICATE(global_var, unmangl_name)
PREDICATE(global_var, type)
PREDICATE(global_var, initializer)
PREDICATE(global_var, section)
PREDICATE(global_var, align)
PREDICATE(global_var, flag)
PREDICATE(global_var, linkage)
PREDICATE(global_var, visibility)
PREDICATE(global_var, threadlocal_mode)
GROUP_END(global_var)

GROUP_BEGIN(alias)
PREDICATE(alias, id)
PREDICATE(alias, name)
PREDICATE(alias, type)
PREDICATE(alias, linkage)
PREDICATE(alias, visibility)
PREDICATE(alias, aliasee)
GROUP_END(alias)

GROUP_BEGIN(function)
PREDICATE(function, id_defn)
PREDICATE(function, id_decl)
PREDICATE(function, unnamed_addr)
PREDICATE(function, linkage)
PREDICATE(function, visibility)
PREDICATE(function, calling_conv)
PREDICATE(function, section)
PREDICATE(function, alignment)
PREDICATE(function, fn_attr)
PREDICATE(function, gc)
PREDICATE(function, pers_fn)
PREDICATE(function, name)
PREDICATE(function, type)
PREDICATE(function, signature)
PREDICATE(function, param)
PREDICATE(function, ret_attr)
PREDICATE(function, param_attr)
GROUP_END(function)

GROUP_BEGIN(instruction)
PREDICATE(instruction, to)
PREDICATE(instruction, flag)
PREDICATE(instruction, next)
PREDICATE(instruction, bb_entry)
PREDICATE(instruction, function)
PREDICATE(instruction, unreachable)
PREDICATE(instruction, pos)
PREDICATE(instruction, location)
GROUP_END(instruction)

GROUP_BEGIN(add)
PREDICATE(add, instr)
PREDICATE(add, first_operand)
PREDICATE(add, second_operand)
GROUP_END(add)

GROUP_BEGIN(fadd)
PREDICATE(fadd, instr)
PREDICATE(fadd, first_operand)
PREDICATE(fadd, second_operand)
GROUP_END(fadd)

GROUP_BEGIN(sub)
PREDICATE(sub, instr)
PREDICATE(sub, first_operand)
PREDICATE(sub, second_operand)
GROUP_END(sub)

GROUP_BEGIN(fsub)
PREDICATE(fsub, instr)
PREDICATE(fsub, first_operand)
PREDICATE(fsub, second_operand)
GROUP_END(fsub)

GROUP_BEGIN(mul)
PREDICATE(mul, instr)
PREDICATE(mul, first_operand)
PREDICATE(mul, second_operand)
GROUP_END(mul)

GROUP_BEGIN(fmul)
PREDICATE(fmul, instr)
PREDICATE(fmul, first_operand)
PREDICATE(fmul, second_operand)
GROUP_END(fmul)

GROUP_BEGIN(udiv)
PREDICATE(udiv, instr)
PREDICATE(udiv, first_operand)
PREDICATE(udiv, second_operand)
GROUP_END(udiv)

GROUP_BEGIN(fdiv)
PREDICATE(fdiv, instr)
PREDICATE(fdiv, first_operand)
PREDICATE(fdiv, second_operand)
GROUP_END(fdiv)

GROUP_BEGIN(sdiv)
PREDICATE(sdiv, instr)
PREDICATE(sdiv, first_operand)
PREDICATE(sdiv, second_operand)
GROUP_END(sdiv)

GROUP_BEGIN(urem)
PREDICATE(urem, instr)
PREDICATE(urem, first_operand)
PREDICATE(urem, second_operand)
GROUP_END(urem)

GROUP_BEGIN(srem)
PREDICATE(srem, instr)
PREDICATE(srem, first_operand)
PREDICATE(srem, second_operand)
GROUP_END(srem)

GROUP_BEGIN(frem)
PREDICATE(frem, instr)
PREDICATE(frem, first_operand)
PREDICATE(frem, second_operand)
GROUP_END(frem)

// Bitwise Binary Instructions

GROUP_BEGIN(shl)
PREDICATE(shl, instr)
PREDICATE(shl, first_operand)
PREDICATE(shl, second_operand)
GROUP_END(shl)

GROUP_BEGIN(lshr)
PREDICATE(lshr, instr)
PREDICATE(lshr, first_operand)
PREDICATE(lshr, second_operand)
GROUP_END(lshr)

GROUP_BEGIN(ashr)
PREDICATE(ashr, instr)
PREDICATE(ashr, first_operand)
PREDICATE(ashr, second_operand)
GROUP_END(ashr)

GROUP_BEGIN(and_)
PREDICATE(and_, instr)
PREDICATE(and_, first_operand)
PREDICATE(and_, second_operand)
GROUP_END(and_)

GROUP_BEGIN(or_)
PREDICATE(or_, instr)
PREDICATE(or_, first_operand)
PREDICATE(or_, second_operand)
GROUP_END(or_)

GROUP_BEGIN(xor_)
PREDICATE(xor_, instr)
PREDICATE(xor_, first_operand)
PREDICATE(xor_, second_operand)
GROUP_END(xor_)

// Terminator Instructions

GROUP_BEGIN(ret)
PREDICATE(ret, instr)
PREDICATE(ret, instr_void)
PREDICATE(ret, operand)
GROUP_END(ret)

GROUP_BEGIN(br)
PREDICATE(br, instr)
PREDICATE(br, instr_cond)
PREDICATE(br, instr_uncond)
PREDICATE(br, condition)
PREDICATE(br, cond_iftrue)
PREDICATE(br, cond_iffalse)
PREDICATE(br, uncond_dest)
GROUP_END(br)

GROUP_BEGIN(switch_)
PREDICATE(switch_, instr)
PREDICATE(switch_, operand)
PREDICATE(switch_, default_label)
PREDICATE(switch_, case_value)
PREDICATE(switch_, case_label)
PREDICATE(switch_, ncases)
GROUP_END(switch_)

GROUP_BEGIN(indirectbr)
PREDICATE(indirectbr, instr)
PREDICATE(indirectbr, address)
PREDICATE(indirectbr, label)
PREDICATE(indirectbr, nlabels)
GROUP_END(indirectbr)

GROUP_BEGIN(resume)
PREDICATE(resume, instr)
PREDICATE(resume, operand)
GROUP_END(resume)

GROUP_BEGIN(invoke)
PREDICATE(invoke, instr)
PREDICATE(invoke, instr_direct)
PREDICATE(invoke, instr_indirect)
PREDICATE(invoke, function)
PREDICATE(invoke, arg)
PREDICATE(invoke, calling_conv)
PREDICATE(invoke, ret_attr)
PREDICATE(invoke, param_attr)
PREDICATE(invoke, fn_attr)
PREDICATE(invoke, normal_label)
PREDICATE(invoke, exc_label)
GROUP_END(invoke)

// Vector Operations

GROUP_BEGIN(extract_element)
PREDICATE(extract_element, instr)
PREDICATE(extract_element, base)
PREDICATE(extract_element, index)
GROUP_END(extract_element)

GROUP_BEGIN(insert_element)
PREDICATE(insert_element, instr)
PREDICATE(insert_element, base)
PREDICATE(insert_element, index)
PREDICATE(insert_element, value)
GROUP_END(insert_element)

GROUP_BEGIN(shuffle_vector)
PREDICATE(shuffle_vector, instr)
PREDICATE(shuffle_vector, first_vector)
PREDICATE(shuffle_vector, second_vector)
PREDICATE(shuffle_vector, mask)
GROUP_END(shuffle_vector)

// Aggregate Operations

GROUP_BEGIN(extract_value)
PREDICATE(extract_value, instr)
PREDICATE(extract_value, base)
PREDICATE(extract_value, index)
PREDICATE(extract_value, nindices)
GROUP_END(extract_value)

GROUP_BEGIN(insert_value)
PREDICATE(insert_value, instr)
PREDICATE(insert_value, base)
PREDICATE(insert_value, value)
PREDICATE(insert_value, index)
PREDICATE(insert_value, nindices)
GROUP_END(insert_value)

// Memory Operations

GROUP_BEGIN(alloca)
PREDICATE(alloca, instr)
PREDICATE(alloca, size)
PREDICATE(alloca, alignment)
PREDICATE(alloca, type)
GROUP_END(alloca)

GROUP_BEGIN(load)
PREDICATE(load, instr)
PREDICATE(load, alignment)
PREDICATE(load, ordering)
PREDICATE(load, address)
PREDICATE(load, isvolatile)
GROUP_END(load)

GROUP_BEGIN(store)
PREDICATE(store, instr)
PREDICATE(store, alignment)
PREDICATE(store, ordering)
PREDICATE(store, value)
PREDICATE(store, address)
PREDICATE(store, isvolatile)
GROUP_END(store)

GROUP_BEGIN(fence)
PREDICATE(fence, instr)
PREDICATE(fence, ordering)
GROUP_END(fence)

GROUP_BEGIN(atomicrmw)
PREDICATE(atomicrmw, instr)
PREDICATE(atomicrmw, ordering)
PREDICATE(atomicrmw, operation)
PREDICATE(atomicrmw, address)
PREDICATE(atomicrmw, value)
PREDICATE(atomicrmw, isvolatile)
GROUP_END(atomicrmw)

GROUP_BEGIN(cmpxchg)
PREDICATE(cmpxchg, instr)
PREDICATE(cmpxchg, address)
PREDICATE(cmpxchg, cmp_value)
PREDICATE(cmpxchg, new_value)
PREDICATE(cmpxchg, ordering)
PREDICATE(cmpxchg, type)
PREDICATE(cmpxchg, isvolatile)
GROUP_END(cmpxchg)

GROUP_BEGIN(gep)
PREDICATE(gep, instr)
PREDICATE(gep, base)
PREDICATE(gep, index)
PREDICATE(gep, nindices)
PREDICATE(gep, inbounds)
GROUP_END(gep)

// Conversion Operations

GROUP_BEGIN(trunc)
PREDICATE(trunc, instr)
PREDICATE(trunc, from_operand)
PREDICATE(trunc, to_type)
GROUP_END(trunc)

GROUP_BEGIN(zext)
PREDICATE(zext, instr)
PREDICATE(zext, from_operand)
PREDICATE(zext, to_type)
GROUP_END(zext)

GROUP_BEGIN(sext)
PREDICATE(sext, instr)
PREDICATE(sext, from_operand)
PREDICATE(sext, to_type)
GROUP_END(sext)

GROUP_BEGIN(fptrunc)
PREDICATE(fptrunc, instr)
PREDICATE(fptrunc, from_operand)
PREDICATE(fptrunc, to_type)
GROUP_END(fptrunc)

GROUP_BEGIN(fpext)
PREDICATE(fpext, instr)
PREDICATE(fpext, from_operand)
PREDICATE(fpext, to_type)
GROUP_END(fpext)

GROUP_BEGIN(fptoui)
PREDICATE(fptoui, instr)
PREDICATE(fptoui, from_operand)
PREDICATE(fptoui, to_type)
GROUP_END(fptoui)

GROUP_BEGIN(fptosi)
PREDICATE(fptosi, instr)
PREDICATE(fptosi, from_operand)
PREDICATE(fptosi, to_type)
GROUP_END(fptosi)

GROUP_BEGIN(uitofp)
PREDICATE(uitofp, instr)
PREDICATE(uitofp, from_operand)
PREDICATE(uitofp, to_type)
GROUP_END(uitofp)

GROUP_BEGIN(sitofp)
PREDICATE(sitofp, instr)
PREDICATE(sitofp, from_operand)
PREDICATE(sitofp, to_type)
GROUP_END(sitofp)

GROUP_BEGIN(ptrtoint)
PREDICATE(ptrtoint, instr)
PREDICATE(ptrtoint, from_operand)
PREDICATE(ptrtoint, to_type)
GROUP_END(ptrtoint)

GROUP_BEGIN(inttoptr)
PREDICATE(inttoptr, instr)
PREDICATE(inttoptr, from_operand)
PREDICATE(inttoptr, to_type)
GROUP_END(inttoptr)

GROUP_BEGIN(bitcast)
PREDICATE(bitcast, instr)
PREDICATE(bitcast, from_operand)
PREDICATE(bitcast, to_type)
GROUP_END(bitcast)

// Other Operations

GROUP_BEGIN(icmp)
PREDICATE(icmp, instr)
PREDICATE(icmp, condition)
PREDICATE(icmp, first_operand)
PREDICATE(icmp, second_operand)
GROUP_END(icmp)

GROUP_BEGIN(fcmp)
PREDICATE(fcmp, instr)
PREDICATE(fcmp, condition)
PREDICATE(fcmp, first_operand)
PREDICATE(fcmp, second_operand)
GROUP_END(fcmp)

GROUP_BEGIN(phi)
PREDICATE(phi, instr)
PREDICATE(phi, type)
PREDICATE(phi, pair_value)
PREDICATE(phi, pair_label)
PREDICATE(phi, npairs)
GROUP_END(phi)

GROUP_BEGIN(select)
PREDICATE(select, instr)
PREDICATE(select, condition)
PREDICATE(select, first_operand)
PREDICATE(select, second_operand)
GROUP_END(select)

GROUP_BEGIN(va_arg)
PREDICATE(va_arg, instr)
PREDICATE(va_arg, va_list)
PREDICATE(va_arg, type)
GROUP_END(va_arg)

GROUP_BEGIN(call)
PREDICATE(call, instr)
PREDICATE(call, instr_direct)
PREDICATE(call, instr_indirect)
PREDICATE(call, function)
PREDICATE(call, arg)
PREDICATE(call, calling_conv)
PREDICATE(call, ret_attr)
PREDICATE(call, param_attr)
PREDICATE(call, fn_attr)
PREDICATE(call, tail)
GROUP_END(call)

GROUP_BEGIN(landingpad)
PREDICATE(landingpad, instr)
PREDICATE(landingpad, type)
PREDICATE(landingpad, catch_clause)
PREDICATE(landingpad, filter_clause)
PREDICATE(landingpad, nclauses)
PREDICATE(landingpad, cleanup)
GROUP_END(landingpad)

// Types

GROUP_BEGIN(primitive_type)
PREDICATE(primitive_type, id)
GROUP_END(primitive_type)

GROUP_BEGIN(integer_type)
PREDICATE(integer_type, id)
GROUP_END(integer_type)

GROUP_BEGIN(fp_type)
PREDICATE(fp_type, id)
GROUP_END(fp_type)

GROUP_BEGIN(type)
PREDICATE(type, alloc_size)
PREDICATE(type, store_size)
GROUP_END(type)

GROUP_BEGIN(func_type)
PREDICATE(func_type, id)
PREDICATE(func_type, varargs)
PREDICATE(func_type, return_type)
PREDICATE(func_type, param_type)
PREDICATE(func_type, nparams)
GROUP_END(func_type)

GROUP_BEGIN(ptr_type)
PREDICATE(ptr_type, id)
PREDICATE(ptr_type, component_type)
PREDICATE(ptr_type, addr_space)
GROUP_END(ptr_type)

GROUP_BEGIN(vector_type)
PREDICATE(vector_type, id)
PREDICATE(vector_type, component_type)
PREDICATE(vector_type, size)
GROUP_END(vector_type)

GROUP_BEGIN(array_type)
PREDICATE(array_type, id)
PREDICATE(array_type, component_type)
PREDICATE(array_type, size)
GROUP_END(array_type)

GROUP_BEGIN(struct_type)
PREDICATE(struct_type, id)
PREDICATE(struct_type, field_type)
PREDICATE(struct_type, field_offset)
PREDICATE(struct_type, field_bit_offset)
PREDICATE(struct_type, nfields)
PREDICATE(struct_type, opaque)
PREDICATE(struct_type, has_name)
GROUP_END(struct_type)

// Variables and constants

GROUP_BEGIN(variable)
PREDICATE(variable, id)
PREDICATE(variable, type)
PREDICATE(variable, source_name)
PREDICATE(variable, pos)
PREDICATE(variable, in_function)
PREDICATE(variable, name)
GROUP_END(variable)

GROUP_BEGIN(constant)
PREDICATE(constant, id)
PREDICATE(constant, type)
PREDICATE(constant, value)
PREDICATE(constant, hash)
PREDICATE(constant, expr)
PREDICATE(constant, to_integer)
PREDICATE(constant, in_function)
GROUP_END(constant)

// Constant hierarchy

GROUP_BEGIN(integer_constant)
PREDICATE(integer_constant, id)
GROUP_END(integer_constant)

GROUP_BEGIN(fp_constant)
PREDICATE(fp_constant, id)
GROUP_END(fp_constant)

GROUP_BEGIN(nullptr_constant)
PREDICATE(nullptr_constant, id)
GROUP_END(nullptr_constant)

GROUP_BEGIN(function_constant)
PREDICATE(function_constant, id)
PREDICATE(function_constant, name)
GROUP_END(function_constant)

GROUP_BEGIN(global_variable_constant)
PREDICATE(global_variable_constant, id)
PREDICATE(global_variable_constant, name)
GROUP_END(global_variable_constant)

GROUP_BEGIN(constant_array)
PREDICATE(constant_array, id)
PREDICATE(constant_array, index)
PREDICATE(constant_array, size)
GROUP_END(constant_array)

GROUP_BEGIN(constant_struct)
PREDICATE(constant_struct, id)
PREDICATE(constant_struct, index)
PREDICATE(constant_struct, size)
GROUP_END(constant_struct)

GROUP_BEGIN(constant_vector)
PREDICATE(constant_vector, id)
PREDICATE(constant_vector, index)
PREDICATE(constant_vector, size)
GROUP_END(constant_vector)

GROUP_BEGIN(constant_expr)
PREDICATE(constant_expr, id)
GROUP_END(constant_expr)

GROUP_BEGIN(bitcast_constant_expr)
PREDICATE(bitcast_constant_expr, id)
PREDICATE(bitcast_constant_expr, from_constant)
GROUP_END(bitcast_constant_expr)

GROUP_BEGIN(inttoptr_constant_expr)
PREDICATE(inttoptr_constant_expr, id)
PREDICATE(inttoptr_constant_expr, from_int_constant)
GROUP_END(inttoptr_constant_expr)

GROUP_BEGIN(ptrtoint_constant_expr)
PREDICATE(ptrtoint_constant_expr, id)
PREDICATE(ptrtoint_constant_expr, from_ptr_constant)
GROUP_END(ptrtoint_constant_expr)

GROUP_BEGIN(gep_constant_expr)
PREDICATE(gep_constant_expr, id)
PREDICATE(gep_constant_expr, base)
PREDICATE(gep_constant_expr, index)
PREDICATE(gep_constant_expr, nindices)
GROUP_END(gep_constant_expr)

GROUP_BEGIN(undef_constant)
PREDICATE(undef_constant, id)
GROUP_END(undef_constant)

GROUP_BEGIN(poison_constant)
PREDICATE(poison_constant, id)
GROUP_END(poison_constant)

// Inline Assembly

GROUP_BEGIN(inline_asm)
PREDICATE(inline_asm, id)
PREDICATE(inline_asm, text)
PREDICATE(inline_asm, constraints)
GROUP_END(inline_asm)

// Function Attributes

GROUP_BEGIN(attribute)
PREDICATE(attribute, target_dependent)
GROUP_END(attribute)

// Signatures

GROUP_BEGIN(signature)
PREDICATE(signature, pts_none)
PREDICATE(signature, pts_return_alloc)
PREDICATE(signature, pts_return_alloc_once)
PREDICATE(signature, pts_return_aliases_arg)
PREDICATE(signature, pts_return_aliases_arg_reachable)
PREDICATE(signature, pts_return_points_to_global)
PREDICATE(signature, pts_return_aliases_global)
PREDICATE(signature, pts_return_aliases_global_reachable)
PREDICATE(signature, pts_arg_alloc)
PREDICATE(signature, pts_arg_alloc_once)
PREDICATE(signature, pts_arg_memcpy_arg)
PREDICATE(signature, pts_arg_memcpy_arg_reachable)
PREDICATE(signature, pts_arg_points_to_global)
PREDICATE(signature, pts_arg_memcpy_global)
PREDICATE(signature, pts_arg_memcpy_global_reachable)
PREDICATE(signature, pts_global_memcpy_arg)
PREDICATE(signature, pts_global_memcpy_arg_reachable)
GROUP_END(signature)

// User options
GROUP_BEGIN(user)
PREDICATE(user, options)
GROUP_END(user)