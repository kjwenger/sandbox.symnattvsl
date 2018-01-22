<style>
.dont {
  visibility: hidden;
}
.dont:after {
  visibility: visible;
  content: 'DON\'T:';
  color: red;
  font-weight: bold;
}
.do {
  visibility: hidden;
}
.do:after {
  visibility: visible;
  content: 'DO:';
  color: green;
  font-weight: bold;
}
</style>

# symnattvsl/cpp - Symmetric NAT Traversal in C++: A C++ Primer

## Table of contents

## Choosing the right build system

## Bootstrapping development

```bash
sudo apt install \
    build-essential \
    gcc g++ \
    graphviz doxygen doxygen-gui
```

## Installing the IDE

## Creating the project

## Structuring the project

- <span class="dont"></span> create one single build file</br>
  `CmakeLists.txt`
- <span class="do"></span> create one build file per substructure</br>
  `CmakeLists.txt ... add_subdirectory(test) ... test/CmakeLists.txt`

## Testing, testing, testing, ...

## Choosing thirdparty code

## Coding

#### Header guards

- <span class="dont"></span> `#ifndef _MY_H`
- <span class="do"></span> `#pragma once`

## Installing dependencies

- When available on both build and target system

- When not available on either build and target system

## Tips and tricks

### Remembering inspirations
- <span class="do"></span> add comments with links to snippets, articles, forums, blogs, ...</br>
  `# http://cprieto.com/posts/2016/10/cmake-out-of-source-build.html`
