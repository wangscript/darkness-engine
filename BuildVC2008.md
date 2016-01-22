# Visual C++ 2008 Express Build #

Let's say we are building all the things in D:\Devel.

1. Visual C++ 2008 Express (http://www.microsoft.com/Express/)<br>
Download and install Visual C++ 2008 Express.<br>
<br>
2. libogg (<a href='http://www.xiph.org/'>http://www.xiph.org/</a>)<br>
Download and extract libogg to D:\Devel. Rename libogg-x.x.x to ogg. Now you should<br>
have directory D:\Devel\ogg which contains several files and dirs like README, Makefile,<br>
src, include, win32 ...<br>
Go to win32 and compile the solution with Visual Studio.<br>
<br>
3. libvorbis (www.xiph.org)<br>
Similar to libogg. Again, extract it as D:\Devel\vorbis (again, you will need to rename<br>
libvorbis-x.x.x to vorbis). Build the solution. If you haven't renamed libogg-x.x.x to ogg in<br>
previous step or you placed it somewhere else, some include files won't be found.<br>
<br>
4. iconv (<a href='http://www.zlatkovic.com/libxml.en.html'>http://www.zlatkovic.com/libxml.en.html</a>)<br>
Download and extract iconv as D:\Devel\iconv.<br>
<br>
5. libxml2 (<a href='http://www.zlatkovic.com/libxml.en.html'>http://www.zlatkovic.com/libxml.en.html</a>)<br>
Download and extract libxml2 as D:\Devel\libxml2.<br>
<br>
6. OpenAL runtime (<a href='http://connect.creativelabs.com/openal/'>http://connect.creativelabs.com/openal/</a>)<br>
Download and install oalinst.<br>
<br>
7. OpenAL SDK (<a href='http://connect.creativelabs.com/openal/'>http://connect.creativelabs.com/openal/</a>)<br>
Download OpenAL11CoreSDK and install it to D:\Devel\OpenAL.<br>
<br>
8. ALUT (<a href='http://connect.creativelabs.com/openal/'>http://connect.creativelabs.com/openal/</a>)<br>
Download and extract ALUT (freealut) as D:\Devel\freealut (again you will have to extract it to<br>
D:\Devel and rename D:\Devel\freealut-x.x.x to D:\Devel\freealut).<br>
<br>
9. SDL (<a href='http://www.libsdl.org/'>http://www.libsdl.org/</a>)<br>
Download SDL-devel-x.x.x-VC8 from "SDL-1.2" and extract it as D:\Devel\SDL.<br>
<br>
10. SDL_image (<a href='http://www.libsdl.org/'>http://www.libsdl.org/</a>)<br>
Find and download SDL_image-devel-x.x.x-VC8 from "Libraries" and extract it as D:\Devel\SDL_image.<br>
<br>
11. CMake (<a href='http://www.cmake.org/'>http://www.cmake.org/</a>)<br>
Download and install CMake.<br>
<br>
12. Dark<br>
Checkout <a href='https://darkness-engine.googlecode.com/svn/trunk/dark'>https://darkness-engine.googlecode.com/svn/trunk/dark</a> into D:\Devel\dark.<br>
Open CMake GUI and drag-drop CMakeLists.txt from D:\Devel\dark to CMake window. Click Configure<br>
twice and then OK. (Of course, you select VS2008 as target when asked).<br>
Build.