# Programming Challenge Solutions

This is a collection of completed and in-progress programming challenge solutions as seen on onlinejudge.com.

I solved many of these over the course of 14 weeks as an exercise for a Programming Challenges class. These solutions are not all optimal, and some of them are simply non-functional. I plan to re-work all incomplete or incorrect solutions in my spare time. I will also attempt to comment my solutions as best I can for readability. Eventually I wish to re-write all correct solutions in Java, Python and Pascal for no other reason than because the onlinejudge in question will accept solutions in those languages. I decided in the end to avoid providing the complete set of test cases I used- Many of them were provided by the helful folks over at UVA Debug. Where possible, though, I'll supply any code I used to generate my own test cases.

Further, I ended up developing a fairly rudimentary script to automatically build and test my solutions- And a script to clean the project directory of all extreneous files. These scripts are included, of course.

I do not endorse the use of the code here for the purposes of academic dishonesty. *Please* don't mess with that. It's not worth it, and will stick with you for the rest of your career.

This repository's being uploaded with the MIT license.

Addendum: 

In August of 2017, libcrypt was marked as depreciated by glibc in a patch that made compiling support for it opt-in. Of course, most packaged versions of glibc would include support for libcrypt for compatability reasons. As time passes, though, support is being phased out wherever possible, for security reasons. The UVA Online judge uses GCC version 5.3.0, and runs it with a set of compiler flags that expect libcrypt support. Most modern versions of GCC, as of 2023 should still be able to work with these compiler flags- As legacy support is a big focus of many distributions, such as Debian. 

It is worth noting, however, that to compile these sources, you *will* need a version of GCC compiled with libcrypt support. Especially in the future, this may necessitate the need for installing the older version of GCC inside of a container, of some sort- Or simply compiling a version of gcc outside of the system path, and hacking around things that way. For the sake of simplicity: downloading, building, and running all of these examples might best be done on an ancient copy of linux inside of a virtual machine.
