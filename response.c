
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "main/php.h"
#include "main/php_streams.h"
#include "Zend/zend_API.h"

#include "php_request.h"

zend_class_entry * PhpResponse_ce_ptr;

/* {{{ Argument Info */
#define AI(method) PhpReponse_##method##_args

ZEND_BEGIN_ARG_INFO_EX(AI(__construct), 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(getVersion), 0, 0, IS_STRING, NULL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(setVersion), 0, 1, IS_NULL, NULL, 0)
    ZEND_ARG_TYPE_INFO(0, version, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(getStatus), 0, 0, IS_LONG, NULL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(setStatus), 0, 1, IS_NULL, NULL, 0)
    ZEND_ARG_TYPE_INFO(0, status, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(getHeaders), 0, 0, IS_ARRAY, NULL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(addSetHeader), 0, 2, IS_NULL, NULL, 0)
    ZEND_ARG_TYPE_INFO(0, label, IS_STRING, 0)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(getCookies), 0, 0, IS_ARRAY, NULL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(setCookie), 0, 1, IS_NULL, NULL, 0)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, expires, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, domain, IS_STRING, 0)
    ZEND_ARG_INFO(0, secure)
    ZEND_ARG_INFO(0, httponly)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI(getContent), 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(setContent), 0, 1, IS_NULL, NULL, 0)
    ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(setContentJson), 0, 1, IS_NULL, NULL, 0)
    ZEND_ARG_INFO(0, content)
    ZEND_ARG_TYPE_INFO(0, options, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, depth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(setContentResource), 0, 1, IS_NULL, NULL, 0)
    ZEND_ARG_TYPE_INFO(0, fh, IS_RESOURCE, 0)
    ZEND_ARG_TYPE_INFO(0, disposition, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, params, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(setDownload), 0, 1, IS_NULL, NULL, 0)
    ZEND_ARG_TYPE_INFO(0, fh, IS_RESOURCE, 0)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, params, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(date), 0, 1, IS_STRING, NULL, 0)
    ZEND_ARG_INFO(0, date)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(AI(send), 0, 0, IS_NULL, NULL, 0)
ZEND_END_ARG_INFO()
/* }}} Argument Info */

/* {{{ proto PhpResponse::__construct() */
PHP_METHOD(PhpResponse, __construct)
{
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::getVersion */

/* {{{ proto string PhpResponse::getVersion() */
PHP_METHOD(PhpResponse, getVersion)
{
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::getVersion */

/* {{{ proto void PhpResponse::setVersion(string $version) */
PHP_METHOD(PhpResponse, setVersion)
{
    zend_string *version;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(version)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::setVersion */

/* {{{ proto int PhpResponse::getStatus() */
PHP_METHOD(PhpResponse, getStatus)
{
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::getStatus */

/* {{{ proto void PhpResponse::setStatus(int $version) */
PHP_METHOD(PhpResponse, setStatus)
{
    zend_long status;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(status)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::setStatus */

/* {{{ proto array PhpResponse::getHeaders() */
PHP_METHOD(PhpResponse, getHeaders)
{
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::getHeaders */

/* {{{ proto void PhpResponse::setHeader(string $label, mixed $value) */
PHP_METHOD(PhpResponse, setHeader)
{
    zend_string *label;
    zval *value;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(label)
        Z_PARAM_ZVAL(value)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::setHeader */

/* {{{ proto void PhpResponse::addHeader(string $label, mixed $value) */
PHP_METHOD(PhpResponse, addHeader)
{
    zend_string *label;
    zval *value;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(label)
        Z_PARAM_ZVAL(value)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::addHeader */

/* {{{ proto array PhpResponse::getCookies() */
PHP_METHOD(PhpResponse, getCookies)
{
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::getCookies */

/* {{{ proto void PhpResponse::setCookie(string name [, string value [, int expires [, string path [, string domain [, bool secure[, bool httponly]]]]]]) */
void php_response_setcookie(INTERNAL_FUNCTION_PARAMETERS, zend_bool raw)
{
    zend_string *name;
    zend_string *value = NULL;
    zend_long expires = 0;
    zend_string *path = NULL;
    zend_string *domain = NULL;
    zend_bool secure = 0;
    zend_bool httponly = 0;

    ZEND_PARSE_PARAMETERS_START(1, 7)
        Z_PARAM_STR(name)
        Z_PARAM_OPTIONAL
        Z_PARAM_STR(value)
        Z_PARAM_LONG(expires)
        Z_PARAM_STR(path)
        Z_PARAM_STR(domain)
        Z_PARAM_BOOL(secure)
        Z_PARAM_BOOL(httponly)
    ZEND_PARSE_PARAMETERS_END();

}

PHP_METHOD(PhpResponse, setCookie)
{
    php_response_setcookie(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}
/* }}} PhpResponse::setCookie */

/* {{{ proto void PhpResponse::setRawCookie(string name [, string value [, int expires [, string path [, string domain [, bool secure[, bool httponly]]]]]]) */
PHP_METHOD(PhpResponse, setRawCookie)
{
    php_response_setcookie(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
/* }}} PhpResponse::setRawCookie */

/* {{{ proto mixed PhpResponse::getContent() */
PHP_METHOD(PhpResponse, getContent)
{
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::getContent */

/* {{{ proto void PhpResponse::setContent(mixed $content) */
PHP_METHOD(PhpResponse, setContent)
{
    zval *content;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(content)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::setContent */

/* {{{ proto void PhpResponse::setContentJson(mixed $value [, int $options [, int $depth = 512]]) */
PHP_METHOD(PhpResponse, setContentJson)
{
    zval *value;
    zend_long options = 0;
    zend_long depth = 512;

    ZEND_PARSE_PARAMETERS_START(1, 3)
        Z_PARAM_ZVAL(value)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(options)
        Z_PARAM_LONG(depth)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::setContentJson */

/* {{{ proto void PhpResponse::setContentResource(resource $fh [, string $disposition [, array $params = array()]]) */
PHP_METHOD(PhpResponse, setContentResource)
{
    zval *zstream;
    zend_string *disposition = NULL;
    zval *params = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 3)
        Z_PARAM_RESOURCE(zstream)
        Z_PARAM_OPTIONAL
        Z_PARAM_STR(disposition)
        Z_PARAM_ARRAY(params)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::setContentResource */

/* {{{ proto void PhpResponse::setDownload(resource $fh [, string $name [, array $params = array()]]) */
PHP_METHOD(PhpResponse, setDownload)
{
    zval *zstream;
    zend_string *name = NULL;
    zval *params = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 3)
        Z_PARAM_RESOURCE(zstream)
        Z_PARAM_OPTIONAL
        Z_PARAM_STR(name)
        Z_PARAM_ARRAY(params)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::setDownload */

/* {{{ proto void PhpResponse::setDownloadInline(resource $fh [, string $name [, array $params = array()]]) */
PHP_METHOD(PhpResponse, setDownloadInline)
{
    zval *zstream;
    zend_string *name = NULL;
    zval *params = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 3)
        Z_PARAM_RESOURCE(zstream)
        Z_PARAM_OPTIONAL
        Z_PARAM_STR(name)
        Z_PARAM_ARRAY(params)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::setDownloadInline */

/* {{{ proto string PhpResponse::date(mixed $date) */
PHP_METHOD(PhpResponse, date)
{
    zval *date;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(date)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::date */

/* {{{ proto void PhpResponse::send() */
PHP_METHOD(PhpResponse, send)
{
    ZEND_PARSE_PARAMETERS_START(0, 0)
    ZEND_PARSE_PARAMETERS_END();
}
/* }}} PhpResponse::send */

/* {{{ PhpResponse methods */
static zend_function_entry PhpResponse_methods[] = {
    PHP_ME(PhpResponse, __construct, AI(__construct), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, getVersion, AI(getVersion), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setVersion, AI(setVersion), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, getStatus, AI(getStatus), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setStatus, AI(setStatus), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, getHeaders, AI(getHeaders), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setHeader, AI(addSetHeader), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, addHeader, AI(addSetHeader), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, getCookies, AI(getCookies), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setCookie, AI(setCookie), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setRawCookie, AI(setCookie), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, getContent, AI(getContent), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setContent, AI(setContent), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setContentJson, AI(setContentJson), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setContentResource, AI(setContentResource), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setDownload, AI(setDownload), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, setDownloadInline, AI(setDownload), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, date, AI(date), ZEND_ACC_PUBLIC)
    PHP_ME(PhpResponse, send, AI(send), ZEND_ACC_PUBLIC)
    PHP_FE_END
};
/* }}} PhpResponse methods */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(response)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "PhpResponse", PhpResponse_methods);
    PhpResponse_ce_ptr = zend_register_internal_class(&ce);

    return SUCCESS;
}
/* }}} PHP_MINIT_FUNCTION */
