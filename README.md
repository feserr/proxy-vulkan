# Proxy Vulkan

[![Build Status](https://travis-ci.org/feserr/proxy-vulkan.svg?branch=master)](https://travis-ci.com/github/feserr/proxy-vulkan)
[![Build Status](https://ci.appveyor.com/api/projects/status/pp3ybojahdt72b6f?svg=true)](https://travis-ci.com/github/feserr/proxy-vulkan)

[![License](https://img.shields.io/badge/license-BSD--2%20clause-blue.svg)](https://github.com/feserr/proxy-vulkan#license)

# Index

- [About](#about)
- [What's New?](#whats-new)
- [How to Build](#how-to-build)
- [How to Run](#how-to-run)
- [Requirements](#requirements)
- [Dependencies](#dependencies)
- [Future features](#future)
- [Contributing](#contributing)
- [Bugs?](#bugs)
- [Honorable mentions?](#mentions)
- [License](#license)

<a name="about"></a>

# Proxy Vulkan 0.2.0

Proxy Vulkan is an open source proxy library for Vulkan.

Version: 0.2.0 - Released: 25th October 2020

<a name="whats-new"></a>

## What's new in 0.1.1?

- Convert to C++.
- Use Cap'n Proto to send the data over TCP.

<a name="how-to-build"></a>

## How to Build

Coming soon...

<a name="how-to-run"></a>

## How to Run (in development)

Currently, the IP are hard-coded.

To run the server:
```bash
./proxy-vulkan-server
```

To run the proxy library, for example for the create instance example:
- Windows:
```bash
./create_instance
```

- MacOS:
```bash
DYLD_LIBRARY_PATH=. ./create_instance
```

- Linux
```bash
LD_LIBRARY_PATH=. ./create_instance
```

<a name="requirements"></a>

## Requirements

- C++14 or above compatible compiler.

<a name="dependencies"></a>

## Dependencies

- [Vulkan](https://vulkan.lunarg.com)
- [Angelia](https://github.com/feserr/angelia)
- [Hephaestus](https://github.com/feserr/hephaestus)
- [Cap'n Proto](https://capnproto.org)

<a name="future"></a>

## Future features

- IP address are configured using a file.

<a name="contributing"></a>

## Contributing

- If you find a bug then please report it on [GitHub Issues][issues].

- If you have a feature request, or have written a game or demo that shows Proxy Vulkan in use, then please get in touch. We'd love to hear from you!

- If you issue a Pull Request for Proxy Vulkan, please only do so against the `dev` branch and **not** against the `master` branch.

<a name="bugs"></a>

## Bugs?

Please add them to the [Issue Tracker][issues] with as much info as possible, especially source code demonstrating the issue.

<a name="mentions"></a>

## Honorable mentions

Coming soon...

<a name="license"></a>

## License

---

<a href="http://opensource.org/licenses/BSD-2-Clause" target="_blank">
<img align="right" width="100" height="137"
 src="https://opensource.org/files/OSI_Approved_License.png">
</a>

    BSD 2-Clause License

    Copyright (c) 2020, Elias Serrano
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    	list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    	this list of conditions and the following disclaimer in the documentation
    	and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

[issues]: https://github.com/feserr/proxy-vulkan/issues
