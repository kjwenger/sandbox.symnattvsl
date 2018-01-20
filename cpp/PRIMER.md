<style>
.dont {color: red;   font-weight: bold;}
.do   {color: green; font-weight: bold;}
</style>

#symnattvsl/cpp - Symmetric NAT Traversal in C++: A C++ Primer

## Table of contents

## Choosing the right build system

## Bootstrapping development

## Installing the IDE

## Creating the project

## Structuring the project

- <span class="dont">DON'T</span>: create one single build file</br>
  `CmakeLists.txt`
- <span class="do">DO</span>: create one build file per substructure</br>
  `CmakeLists.txt ... add_subdirectory(test) ... test/CmakeLists.txt`

## Testing, testing, testing, ...

## Choosing thirdparty code

## Coding

#### Header guards

- <span class="dont">DON'T</span>: `#ifndef _MY_H`
- <span class="do">DO</span>: `#pragma once`

## Installing dependencies

- When available on both build and target system

- When not available on either build and target system

## Tips and tricks

### Remembering inspirations
- <span class="do">DO</span>: add comments with links to snippets, articles, forums, blogs, ...</br>
  `# http://cprieto.com/posts/2016/10/cmake-out-of-source-build.html`
