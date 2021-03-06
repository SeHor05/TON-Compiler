// Auxiliary file, defining three sets of C symbols for a structure:
// - enumeration with fields offsets and lengths
// - serialization methods
// - deserialization methods
//
// Two macroses should be specified to use this file: TON_STRUCT_NAME
// and TON_STRUCT. The structure should be specified in TON_STRUCT macro, 
// it may use the following macros: 

// Structure serialization
#define FIELD_CONSTANT_UNSIGNED(name, value, size) { *builder = __builtin_tvm_stu(value, *builder, size); }
#define FIELD_UNSIGNED(name, size)                 { *builder = __builtin_tvm_stu(value->name, *builder, size); }
#define FIELD_SIGNED(name, size)                   { *builder = __builtin_tvm_sti(value->name, *builder, size); }
#define FIELD_VAR_UNSIGNED(name, size)             { *builder = __builtin_tvm_stu(value->name.len, *builder, size); \
                                                     *builder = __builtin_tvm_stu(value->name.value, *builder, value->name.len * 8); }
#define FIELD_VAR_SIGNED(name, size)               { *builder = __builtin_tvm_stu(value->name.len, *builder, size); \
                                                     *builder = __builtin_tvm_sti(value->name.value, *builder, value->name.len * 8); }
#define FIELD_COMPLEX(name, type)                  Serialize_##type##_Impl(builder, &(value->name));
#define FIELD_MAYBE(name, type)                    { if (value->name.just) { \
                                                       *builder = __builtin_tvm_stu(1, *builder, 1); \
                                                       Serialize_##type##_Impl(builder, &(value->name.value)); \
                                                     } else { \
                                                       *builder = __builtin_tvm_stu(0, *builder, 1); \
                                                     } \
                                                   }
#define FIELD_ARRAY(name, actual_size, max_size, type) { /* TODO */ }

void XJOIN3(Serialize_, TON_STRUCT_NAME, _Impl)(__tvm_builder* builder, TON_STRUCT_NAME* value) {
    TON_STRUCT
}

void XJOIN(Serialize_, TON_STRUCT_NAME)(TON_STRUCT_NAME* value) {
    __tvm_builder builder = __builtin_tvm_newc();
    XJOIN3(Serialize_, TON_STRUCT_NAME, _Impl)(&builder, value);
    __builtin_tvm_setglobal(6, __builtin_tvm_cast_from_builder(builder));
}

#undef FIELD_CONSTANT_UNSIGNED
#undef FIELD_UNSIGNED
#undef FIELD_SIGNED
#undef FIELD_VAR_UNSIGNED
#undef FIELD_VAR_SIGNED
#undef FIELD_COMPLEX
#undef FIELD_MAYBE
#undef FIELD_ARRAY

// Structure deserialization
#define FIELD_CONSTANT_UNSIGNED(name, value, size) { int  v; *slice = __tvm_ldu(*slice, size, &v); tvm_assert (v == value, 59); }
#define FIELD_UNSIGNED(name, size)                 { int  v; *slice = __tvm_ldu(*slice, size, &v); res.name = v; }
#define FIELD_SIGNED(name, size)                   { int  v; *slice = __tvm_ldi(*slice, size, &v); res.name = v; }
#define FIELD_VAR_UNSIGNED(name, size)             { int v1; *slice = __tvm_ldu(*slice, size, &v1); res.name.len = v1; \
                                                     int v2; *slice = __tvm_ldu(*slice, res.name.len * 8, &v2); res.name.value = v2; }
#define FIELD_VAR_SIGNED(name, size)               { int v1; *slice = __tvm_ldu(*slice, size, &v1); res.name.len = v1; \
                                                     int v2; *slice = __tvm_ldi(*slice, res.name.len * 8, &v2); res.name.value = v2; }
#define FIELD_COMPLEX(name, type)                  { res.name = Deserialize_##type##_Impl(slice); }
#define FIELD_MAYBE(name, type)                    { int v;  *slice = __tvm_ldu(*slice, 1, &v); res.name.just = v; \
                                                     if (res.name.just) res.name.value = Deserialize_##type##_Impl(slice); }
#define FIELD_ARRAY(name, actual_size, max_size, type) { /* TODO*/ }

TON_STRUCT_NAME XJOIN3(Deserialize_, TON_STRUCT_NAME, _Impl)(__tvm_slice* slice) {
    TON_STRUCT_NAME res;
    TON_STRUCT
    return res;
}

TON_STRUCT_NAME XJOIN(Deserialize_, TON_STRUCT_NAME)() {
    __tvm_slice slice = __builtin_tvm_cast_to_slice(__builtin_tvm_getglobal(3));
    TON_STRUCT_NAME s = XJOIN3(Deserialize_, TON_STRUCT_NAME, _Impl)(&slice);
    __builtin_tvm_setglobal(3, __builtin_tvm_cast_from_slice(slice));
    return s;
}

#undef FIELD_CONSTANT_UNSIGNED
#undef FIELD_UNSIGNED
#undef FIELD_SIGNED
#undef FIELD_VAR_UNSIGNED
#undef FIELD_VAR_SIGNED
#undef FIELD_COMPLEX
#undef FIELD_MAYBE
#undef FIELD_ARRAY

#undef TON_STRUCT_NAME
#undef TON_STRUCT
