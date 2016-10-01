
# ext/request

This extension provides fundamental server-side request and response objects for PHP. These are *not* HTTP message objects proper. They are more like wrappers for existing global PHP variables and functions, with some limited additional convenience functionality.

This extension provides two classes:

- StdRequest, composed of read-only copies of PHP superglobals and some other commonly-used values, with methods for adding application-specific request information in immutable fashion.

- StdResponse, essentially a wrapper around (and buffer for) response-related PHP functions, with some additional convenience methods, and self-sending capability

## StdRequest

An object representing the PHP request information.

- Provide non-session superglobals as read-only properties.

- Add other read-only properties calculated from the superglobals ($method, $headers, $content, etc.).

- Allow for adding application-specific information, such as parsed body and  path-info or routing parameters, in immutable fashion.

- Extendable so users can add custom functionality.

### Instantiation

Instantiation of _StdRequest_ is straightforward:

```php
<?php
$request = new StdRequest();
?>
```

The _StdRequest_ object builds itself from the PHP superglobals. If you want to provide custom values in place of the superglobals, pass an array that mimics `$GLOBALS` to the constructor:

```php
<?php
$request = new StdRequest([
    '_SERVER' => [
        'foo' => 'bar',
    ],
]);
?>
```

If a superglobal is represented in the array of custom values, it will be used instead of the real superglobal. If it is not represented in the array, _StdRequest_ will use the real superglobal.

### Properties

_StdRequest_ has these public properties.

#### Superglobal-related

- `$env`: A copy of `$_ENV`.
- `$files`: A copy of `$_FILES`.
- `$get`: A copy of `$_GET`.
- `$cookie`: A copy of `$_COOKIE`.
- `$post`: A copy of `$_POST`.
- `$server`: A copy of `$_SERVER`.
- `$uploads`: A copy of `$_FILES`, restructured to look more like `$_POST`.

Notes:

These properties are read-only and cannot be modified.

#### HTTP-related

- `$acceptCharset`: An array computed from `$_SERVER['HTTP_ACCEPT_CHARSET']`.
- `$acceptEncoding`: An array computed from `$_SERVER['HTTP_ACCEPT_ENCODING']`.
- `$acceptLanguage`: An array computed from `$_SERVER['HTTP_ACCEPT_LANGUAGE']`.
- `$acceptMedia`: An array computed from `$_SERVER['HTTP_ACCEPT']`.
- `$headers`: An array of all `HTTP_*` header keys from `$_SERVER`, plus RFC 3875 headers not prefixed with `HTTP_`
- `$method`: The `$_SERVER['REQUEST_METHOD']` value, or the `$_SERVER['HTTP_X_HTTP_METHOD_OVERRIDE']` when appropriate.
- `$url`: The result of [`parse_url`](http://php.net/parse_url) as built from the `$_SERVER` keys `HTTPS`, `HTTP_HOST`/`SERVER_NAME`, `SERVER_PORT`, and `REQUEST_URI`.
- `$xhr`: A boolean indicating if this is an XmlHttpRequest.

Notes:

These properties are read-only and cannot be modified.

Each element of the `$accept*` arrays has these sub-array keys:

```
'value' => The "main" value of the accept specifier
'quality' => The 'q=' parameter value
'params' => A key-value array of all other parameters
```

In addition, each `$acceptLanguage` array element has two additional sub-array keys: `'type'` and `'subtype'`.

The `$accept*` array elements are sorted by highest `q` value to lowest.

#### Content-related

- `$content`: The value of `file_get_contents('php://input')`.
- `$contentCharset`: The `charset` parameter value of `$_SERVER['CONTENT_TYPE']`.
- `$contentLength`: The value of `$_SERVER['CONTENT_LENGTH']`.
- `$contentMd5`: The value of `$_SERVER['HTTP_CONTENT_MD5']`.
- `$contentType`: The value of `$_SERVER['CONTENT_TYPE']`, minus any parameters.

Notes:

These properties are read-only and cannot be modified.

#### Authentication-related

- `$authDigest`: An array of digest values computed from `$_SERVER['PHP_AUTH_DIGEST']`.
- `$authPw`: The value of `$_SERVER['PHP_AUTH_PW']`.
- `$authType`: The value of `$_SERVER['PHP_AUTH_TYPE']`.
- `$authUser`: The value of `$_SERVER['PHP_AUTH_USER']`.

Notes:

These properties are read-only and cannot be modified.

#### Application-related

- `$input`: Typically the parsed content of the request.
- `$params`: Typically path-info or routing parameters.

Notes:

These property values are "immutable" rather than read-only. That is, they can changed using the methods below, but the changed values are available only on a new instance of the _StdRequest_ as returned by the method.

### Methods

The _StdRequest_ object has these public methods:

#### `withInput(mixed $input)`

Sets the `$input` value on a clone of the called _StdRequest_ instance.

For example:

```php
<?php
$request = new StdRequest();
if ($request->contentType == 'application/json') {
    $input = json_decode($request->content, true);
    $request = $request->withInput($input);
}
?>
```

Note that this method returns a clone of the _StdRequest_ instance with the new property value. It does not modify the property value on the called instance.

The value may be null, scalar, or array. Arrays are recursively checked to make sure they contain only null, scalar, or array values; this is to preserve immutability of the value.

#### `withParam(mixed $key, mixed $val)`

Sets the value of one `$params` key on a clone of the called _StdRequest_ instance.

For example:

```php
<?php
$request = new StdRequest();
var_dump($request->params); // []

$request = $request->withParam('foo', 'bar');
var_dump($request->params); // ['foo' => 'bar']
?>
```

Note that this method returns a clone of the _StdRequest_ instance with the new property value. It does not modify the property value on the called instance.

The value may be null, scalar, or array. Arrays are recursively checked to make sure they contain only null, scalar, or array values; this is to preserve immutability of the value.


#### `withParams(array $params)`

Sets the `$params` value on a clone of the called _StdRequest_ instance.

For example:

```php
<?php
$request = new StdRequest();
var_dump($request->params); // []

$request = $request->withParams(['foo' => 'bar']);
var_dump($request->params); // ['foo' => 'bar']
?>
```

Note that this method returns a clone of the _StdRequest_ instance with the new property value. It does not modify the property value on the called instance.

The value may be null, scalar, or array. Arrays are recursively checked to make sure they contain only null, scalar, or array values; this is to preserve immutability of the value.

#### `withoutParam(mixed $key)`

Unsets a single `$params` key on a clone of the called _StdRequest_ instance.

For example:

```php
<?php
$request = new StdRequest();
$request = $request->withParams(['foo' => 'bar', 'baz' => 'dib']);
var_dump($request->params); // ['foo' => 'bar', 'baz' => 'dib']

$request = $request->withoutParam('baz');
var_dump($request->params); // ['foo' => 'bar']
?>
```

Note that this method returns a clone of the _StdRequest_ instance with the new property value. It does not modify the property value on the called instance.

#### `withoutParams([array $keys = null])`

Unsets multiple `$params` keys on a clone of the called _StdRequest_ instance.

For example:

```php
<?php
$request = new StdRequest();
$request = $request->withParams([
    'foo' => 'bar',
    'baz' => 'dib',
    'zim' => 'gir',
]);
var_dump($request->params); // ['foo' => 'bar', 'baz' => 'dib', 'zim' => 'gir']

$request = $request->withoutParams(['baz', 'zim']);
var_dump($request->params); // ['foo' => 'bar']
?>
```

Calling `withoutParams()` with no arguments removes all `$params` on a clone of the called _StdRequest_ instance:

```php
<?php
$request = new StdRequest();
$request = $request->withParams([
    'foo' => 'bar',
    'baz' => 'dib',
    'zim' => 'gir',
]);
var_dump($request->params); // ['foo' => 'bar', 'baz' => 'dib', 'zim' => 'gir']

$request = $request->withoutParams();
var_dump($request->params); // []
?>
```

Note that this method returns a clone of the _StdRequest_ instance with the new property value. It does not modify the property value on the called instance.

## StdResponse

Goals:

- Light wrapper around PHP functions (with similar lack of validation)
- Buffer for headers and cookies
- Helper for HTTP date
- Helper for comma- and semicolon-separated header values
- Minimalist support for sending a file, and sending json
- Self-sendable
- Mutable, extendable

## Instantiation

Instantation is straightforward:

```php
<?php
$response = new StdResponse();
?>
```

### Properties

_StdResponse_ has no public properties.

### Methods

_StdResponse_ has these public methods.

#### HTTP Version

- `setVersion($version)`: Sets the HTTP version for the response (typically '1.0' or '1.1').

- `getVersion()`: Returns the HTTP version for the response.

#### Status Code

- `setStatus($status)`: Sets the HTTP response code; a buffered equivalent of `http_response_code($status)`.

- `getStatus()`: Gets the HTTP response code.

#### Headers

- `setHeader($label, $value)`: Overwrites an HTTP header; a buffered equivalent of `header("$label: $value", true)`.

- `addHeader($label, $value)`: Adds an HTTP header; a buffered equivalent of `header("$label: $value", false)`.

- `date($date)`: Returns a RFC 1123 formatted date. The `$date` argument can be any recognizable date-time string, or a _DateTime_ object.

- `getHeaders()`: Returns the array of headers to be sent.

Notes:

The `$value` in a `setHeader()` or `addHeader()` call may be an array, in which case it will be converted to a comma-separated and/or semicolon-separated value string. For example:

```php
<?php
$response = new StdResponse();

$response->setHeader('Cache-Control', [
    'public',
    'max-age' => '123',
    's-maxage' => '456',
    'no-cache',
]); // Cache-Control: public, max-age=123, s-maxage=456, no-cache

$response->setHeader('Content-Type', [
    'text/plain' => [
        'charset' => 'utf-8'
    ],
]); // Content-Type: text/plain;charset=utf-8

$response->setHeader('X-Whatever', [
    'foo',
    'bar' => [
        'baz' => 'dib',
        'zim',
        'gir' => 'irk',
    ],
    'qux' => 'quux',
]); // X-Whatever: foo, bar;baz=dib;zim;gir=irk, qux=quux
```

Finally, the header field labels are retained internally in lower-case, and are sent as lower-case. This is to [comply with HTTP/2 requirements](https://tools.ietf.org/html/rfc7540#section-8.1.2); while HTTP/1.x has no such requirement, lower-case is also recognized as valid.

#### Cookies

- `setCookie(...)`: A buffered equivalent of [`setcookie()`](http://php.net/setcookie) with identical arguments.

- `setRawCookie(...)`: A buffered equivalent of [`setrawcookie()`](http://php.net/setrawcookie) with identical arguments.

- `getCookies()`: Returns the array of cookies to be sent.

#### Content

- `setContent($content)`: Sets the content of the response. This can be a string or resource (or anything else).

- `setContentJson($value, $options = 0, $depth = 512)`: A convenience method to `json_encode($value)` as the response content, and set a `Content-Type: application/json` header.

- `setContentResource($fh, $disposition, array $params = [])`: A convenience method to set the content to a resource (typically a file handle), as well as set the headers for `Content-Type: application/octet-stream`, `Content-Transfer-Encoding: binary`, and `Content-Disposition: $disposition`.  (The `$params` key-value array is added as parameters on the disposition.)

- `setDownload($fh, $name, array $params = [])`: A convenience method to set the content to a resource (typically a file handle), to be downloaded as `$name`, with `Content-Disposition: attachment`.   (The `$params` key-value array is added as parameters on the disposition.)

- `setDownloadInline($fh, $name, array $params = [])`: A convenience method to set the content to a resource (typically a file handle), to be downloaded as `$name`, with `Content-Disposition: inline`.   (The `$params` key-value array is added as parameters on the disposition.)

- `getContent()`: Returns the content of the response; this may be a string or resource (or anything else).

#### Sending

- `send()`: This sends the response version, status, headers, and cookies using native PHP functions `header()`, `setcookie()`, and `setrawcookie()`. Then, if the response content is a resource, it is sent with `fpassthru()`; if a callable object or closure, it is invoked; otherwise, the content is `echo`ed.
