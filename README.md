<div id="top"></div>


<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This repo contains the source code for the UTS 32933 Research Project. To extend the flexibility of the currrent SVF-tool, a Python port of the SVF-example is developed. Furthermore, the `Docker` is used for a better distribution purpose.

- Name: Jiawei Wang
- ID: 14210429
- Supervised by: Yulei Sui

<p align="right">(<a href="#top">back to top</a>)</p>




<!-- GETTING STARTED -->
## Getting Started

To run this `SVF-tool` externally with python port, please use `Docker` to build it and run it.

### Prerequisites

`Docker` is the only thing you need to run this project. Since we need several dependencies to run the SVF-tools

### Installation

_Below is an example of how you can instruct your audience on installing and setting up your app. This template doesn't rely on any external dependencies or services._

1. Install the [Docker](https://www.docker.com/get-started/)

2. Clone this repo

```bash
git clone https://github.com/Kyle505/svf-python.git
```

3. Change workdir into cloned project

```bash
cd svf-python
```

4. Build the Docker image, names it as python-svf

```bash
docker build . -t python-svf
```

5. Run it
```bash
docker run -it python-svf
```

_Python script and env stuff should be setup automatically, DockerFile comes from official SVF-tool, and certain modification was made_



<p align="right">(<a href="#top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage


1. Run python script

After launch the Docker, the workdir should be set as the following

> root@6ef008b4185e:/home/SVF-example#

Simply run the command below

```
python3 run.py --file example.c
```

output:
```
*********CallGraph Stats***************
################ (program : )###############
-------------------------------------------------------
CalRetPairInCycle   0
MaxNodeInCycle      0
NodeInCycle         0
TotalEdge           1
TotalCycle          0
TotalNode           3
#######################################################

*********General Stats***************
################ (program : )###############
BBWith2Succ         0
LocalVarInRecur     0
BBWith3Succ         0
TotalCallSite       1
NonPtrObj           6
VarStructObj        0
ConstStructObj      0
StackObjs           7
HeapObjs            0
GlobalObjs          0
...
...
...
FIObjNum            0
TotalPTASVFStmts    27
TotalSVFStmts       29
CopysNum            1
FSObjNum            11
StoresNum           7
TotalFieldObjects   0
AddrsNum            11
-------------------------------------------------------
#######################################################
```

Note that any c code can be replaced in the argument `--file`, everything will be compiled with LLVM and analyzed by SVF.


<p align="right">(<a href="#top">back to top</a>)</p>




