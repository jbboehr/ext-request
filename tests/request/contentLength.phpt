--TEST--
StdRequest::$contentLength
--SKIPIF--
<?php if( !extension_loaded('request') ) die('skip '); ?>
--FILE--
<?php
$_SERVER = [
    'HTTP_HOST' => 'example.com',
    'HTTP_CONTENT_LENGTH' => '123',
];
$request = new StdRequest();
var_dump($request->contentLength);

unset($_SERVER['HTTP_CONTENT_LENGTH']);
$request = new StdRequest();
var_dump($request->contentMd5);
--EXPECT--
string(3) "123"
NULL
