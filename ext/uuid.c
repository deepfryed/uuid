#include <ruby/ruby.h>
#include <uuid/uuid.h>

#define ID_CONST_GET rb_intern("const_get")
#define CONST_GET(scope, constant) (rb_funcall(scope, ID_CONST_GET, 1, rb_str_new2(constant)))

static VALUE cUUID;
static VALUE eRuntimeError;
static VALUE eArgumentError;
static VALUE eStandardError;

VALUE rb_uuid_create(uuid_t uuid_b) {
    VALUE rv   = rb_obj_alloc(cUUID);
    VALUE uuid = rb_str_new((char *)uuid_b, 16);
    VALUE args[1] = { uuid };
    rb_obj_call_init(rv, 1, args);
    return rv;
}

VALUE rb_uuid_parse (VALUE self, VALUE v) {
    uuid_t uuid_b;
    if(uuid_parse(RSTRING_PTR(v), uuid_b) != 0)
        rb_raise(eArgumentError, "failed to parse uuid string");
    return rb_uuid_create(uuid_b);
}

VALUE rb_uuid_generate(VALUE self) {
    uuid_t uuid_b;
    uuid_generate(uuid_b);
    return rb_uuid_create(uuid_b);
}

VALUE rb_uuid_generate_time(VALUE self) {
    uuid_t uuid_b;
    uuid_generate_time(uuid_b);
    return rb_uuid_create(uuid_b);
}

VALUE rb_uuid_generate_random(VALUE self) {
    uuid_t uuid_b;
    uuid_generate_random(uuid_b);
    return rb_uuid_create(uuid_b);
}

VALUE rb_uuid_compare(VALUE self, VALUE other) {
    uuid_t uuid_b1;
    uuid_t uuid_b2;
    memcpy(uuid_b1, RSTRING_PTR(rb_iv_get(self,  "@uuid")), 16);
    memcpy(uuid_b2, RSTRING_PTR(rb_iv_get(other, "@uuid")), 16);
    return INT2NUM(uuid_compare(uuid_b1, uuid_b2));
}

VALUE rb_uuid_variant(VALUE self) {
    uuid_t uuid_b;
    memcpy(uuid_b, RSTRING_PTR(rb_iv_get(self,  "@uuid")), 16);
    return INT2NUM(uuid_variant(uuid_b));
}

void rb_uuid_initialize(VALUE self, VALUE uuid) {
    rb_iv_set(self, "@uuid", uuid);
}

void Init_uuid(void) {

    cUUID = rb_define_class("UUID", rb_cObject);
    eRuntimeError  = CONST_GET(rb_mKernel, "RuntimeError");
    eArgumentError = CONST_GET(rb_mKernel, "ArgumentError");
    eStandardError = CONST_GET(rb_mKernel, "StandardError");

    rb_define_const(cUUID, "UUID_VARIANT_NCS", INT2NUM(0));
    rb_define_const(cUUID, "UUID_VARIANT_DCE", INT2NUM(1));
    rb_define_const(cUUID, "UUID_VARIANT_MICROSOFT", INT2NUM(2));
    rb_define_const(cUUID, "UUID_VARIANT_OTHER", INT2NUM(3));
    rb_define_const(cUUID, "UUID_TYPE_DCE_TIME", INT2NUM(1));
    rb_define_const(cUUID, "UUID_TYPE_DCE_RANDOM", INT2NUM(4));
    rb_define_module_function(cUUID, "parse", rb_uuid_parse, 1);
    rb_define_module_function(cUUID, "generate", rb_uuid_generate, 0);
    rb_define_module_function(cUUID, "generate_random", rb_uuid_generate_random, 0);
    rb_define_module_function(cUUID, "generate_time", rb_uuid_generate_time, 0);
    rb_define_method(cUUID, "compare", rb_uuid_compare, 1);
    rb_define_alias(cUUID, "<=>", "compare");
    rb_define_method(cUUID, "variant", rb_uuid_variant, 0);
    rb_define_method(cUUID, "initialize", RUBY_METHOD_FUNC(rb_uuid_initialize), 1);
}
