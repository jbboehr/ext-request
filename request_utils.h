
#ifndef REQUEST_UTILS_H
#define REQUEST_UTILS_H

#include "main/php.h"

zend_bool php_request_is_secure(zval *server);
void php_request_normalize_headers(zval *return_value, zval *server);
void php_request_parse_accepts(zval *return_value, const unsigned char *str, size_t len);

#endif	/* PHP_REQUEST_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
