# Shell

This is a basic implementation of a unix shell written in C.
It supports:

* Simple commands
* Simple IO redirection
* Multiple piping
* Run program in background 

It has many limitations. To name a few:

* Proper checking for all invalid commands
* No escaping and quoting
* No error redirection

I intend to improve this shell to add more features, and gradually 
remove limitations in the future. 

Dependencies
-------------

Requires the GNU Readline Library (libreadline6 libreadline6-dev)

License
--------

This repository is licenced under the MIT lincense.
