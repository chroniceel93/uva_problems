# Programming Challenge Solutions

This is a collection of completed and in-progress programming challenge solutions as seen on onlinejudge.com.

I solved many of these over the course of 14 weeks as an exercise for a Programming Challenges class. These solutions are not all optimal, and some of them are simply non-functional. I plan to re-work all incomplete or incorrect solutions in my spare time. I will also attempt to comment my solutions as best I can for readability. Eventually I wish to re-write all correct solutions in Java, Python and Pascal for no other reason than because the onlinejudge in question will accept solutions in those languages. I decided in the end to avoid providing the complete set of test cases I used- Many of them were provided by the helful folks over at UVA Debug. Where possible, though, I'll supply any code I used to generate my own test cases.

Further, I ended up developing a fairly rudimentary script to automatically build and test my solutions- And a script to clean the project directory of all extreneous files. These scripts are included, of course.

I do not endorse the use of the code here for the purposes of academic dishonesty. *Please* don't mess with that. It's not worth it, and will stick with you for the rest of your career.

This repository's being uploaded with the MIT license.

Addendum: 

In August of 2017, libcrypt was marked as depreciated by glibc in a patch that made compiling support for it opt-in. Of course, most packaged versions of glibc would include support for libcrypt for compatability reasons. As time passes, though, support is being phased out wherever possible, for security reasons. The UVA Online judge uses an older version of glibc that has support for this library built in, but your current toolchain may not have it available, and the compiler will spit out an error when trying to link to it. To compile the c++ sources with the same build flags that the online juge would expect, for the purpose of testing and debugging the code, you may need to link against an older version of glibc. Beware of attempting to do so- Aside from simply spinning up a virtual machine or container with an older version of linux, you *will* run into some interesting problems along the way.
