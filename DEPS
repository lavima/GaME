# Base on code from https://github.com/victorgomes/v8-gn-example 
# Original LICENSE can be found in LICENSE.v8-gn-example

gclient_gn_args_file = 'game/build/config/gclient_args.gni'

gclient_gn_args = [
  'checkout_google_benchmark',
]

vars = {
  'checkout_google_benchmark' : False,

  'abseil_cpp_revision': '66b870c3b1cbbb7f85b31cc9a8a785329f5ebcb8',
  'abseil_cpp_url': 'https://chromium.googlesource.com/chromium/src/third_party/abseil-cpp.git',

  'build_revision': 'ae5b5ecabdc944bde2730e6b7d13abe71ca9a2ee',
  'build_url': 'https://chromium.googlesource.com/chromium/src/build.git',
  # Updated to GaME fork of build setup
  #'build_revision': '7c664f9cb50a4308933bc44d0ada2e7516f4f095',
  #'build_url': 'https://github.com/lavima/game-build.git',


  'buildtools_revision': '4be464e050b3d05060471788f926b34c641db9fd',
  'buildtools_url': 'https://chromium.googlesource.com/chromium/src/buildtools.git',

  'buildtools_clang_format_revision': 'bb994c6f067340c1135eb43eed84f4b33cfa7397',
  'buildtools_clang_format_url': 'https://chromium.googlesource.com/chromium/llvm-project/cfe/tools/clang-format.git',

  'buildtools_libcxx_revision': '78d6a7767ed57b50122a161b91f59f19c9bd0d19',
  'buildtools_libcxx_url': 'https://chromium.googlesource.com/chromium/llvm-project/libcxx.git',

  'buildtools_libcxxabi_revision': 'ce3db128f9e4d6d19d1cdbe39bb45fcc64a5adb0',
  'buildtools_libcxxabi_url': 'https://chromium.googlesource.com/chromium/llvm-project/libcxxabi.git',

  'buildtools_libunwind_revision': '3e6ec2ae9afaa3683269b690612f84d907943ea2',
  'buildtools_libunwind_url': 'https://chromium.googlesource.com/external/llvm.org/libunwind.git',

  'clang_revision': 'd4827bfe100154b06d9ffa59b21bb845fce9c7d5',
  'clang_url': 'https://chromium.googlesource.com/chromium/src/tools/clang.git',

  'depot_tools_revision': '6e970e597b25a3a74a560746711d1811133841d2',
  'depot_tools_url': 'https://chromium.googlesource.com/chromium/tools/depot_tools.git',

  # GN CIPD package version.
  'gn_version': 'git_revision:81ee1967d3fcbc829bac1c005c3da59739c88df9',

  'googletest_revision': '07f4869221012b16b7f9ee685d94856e1fc9f361',
  'googletest_url': 'https://chromium.googlesource.com/external/github.com/google/googletest.git',

  'icu_revision': '7db579a73addda0edb2bb83465ae51bcdc601af7',
  'icu_url': 'https://chromium.googlesource.com/chromium/deps/icu.git',

  'jinja2_revision': 'a82a4944a7f2496639f34a89c9923be5908b80aa',
  'jinja2_url': 'https://chromium.googlesource.com/chromium/src/third_party/jinja2.git',

  'markupsafe_revision': 'f2fb0f21ef1e1d4ffd43be8c63fc3d4928dea7ab',
  'markupsafe_url': 'https://chromium.googlesource.com/chromium/src/third_party/markupsafe.git',

  'trace_common_revision' : 'ea3ab7b3f22a844966f27bcafc0475e4ea95a019',
  'trace_common_url': 'https://chromium.googlesource.com/chromium/src/base/trace_event/common.git',

  #'v8_revision': 'bc0bfbe84059da4989474e1bbe1282ebcf72886d',
  # Updated to version 8.7
  'v8_revision': 'c588e020c2240c51cdc4b7563f96c48ab6af0751',

  'v8_url': 'https://chromium.googlesource.com/v8/v8.git',

  'zlib_revision': 'd7f3ca98b2b0d5f72656502961a59353791c4f8a',
  'zlib_url': 'https://chromium.googlesource.com/chromium/src/third_party/zlib.git',

# GaME Variables

  'glfw_url': 'https://github.com/glfw/glfw.git',
  'glfw_revision': '7e8da57094281c73a0be5669a4b79686b4917f6c',

  'glm_url': 'https://github.com/g-truc/glm.git',
  'glm_revision': '24a4befe80171966758983173f381ce1ef6c839f',

  'imgui_url': 'https://github.com/ocornut/imgui.git',
  'imgui_revision': '9874077fc0e364383ef997e3d4332172bfddc0b9',

  'pugixml_url': 'https://github.com/zeux/pugixml.git',
  'pugixml_revision': '5a0fd5d85f2b31f44c8df84a4bc51f453cef57ac',

  'stb_url': 'https://github.com/nothings/stb.git',
  'stb_revision': 'b42009b3b9d4ca35bc703f5310eedc74f584be58',

  'vulkan_headers_url': 'https://github.com/KhronosGroup/Vulkan-Headers.git',
  'vulkan_headers_revision': '7f9879b1b1fab53f719a9ed5e6e29533b10972b2',

}
deps = {
  'game/base/trace_event/common': Var('trace_common_url') + '@' + Var('trace_common_revision'),
  'game/build': Var('build_url') + '@' + Var('build_revision'),
  'game/buildtools': Var('buildtools_url') + '@' + Var('buildtools_revision'),
  'game/buildtools/clang_format/script': Var('buildtools_clang_format_url') + '@' + Var('buildtools_clang_format_revision'),
  'game/buildtools/third_party/libc++/trunk': Var('buildtools_libcxx_url') + '@' + Var('buildtools_libcxx_revision'),
  'game/buildtools/third_party/libc++abi/trunk': Var('buildtools_libcxxabi_url') + '@' + Var('buildtools_libcxxabi_revision'),
  'game/buildtools/third_party/libunwind/trunk': Var('buildtools_libunwind_url') + '@' + Var('buildtools_libunwind_revision'),
  'game/third_party/abseil-cpp': Var('abseil_cpp_url') + '@' + Var('abseil_cpp_revision'),
  'game/third_party/depot_tools': Var('depot_tools_url') + '@' + Var('depot_tools_revision'),
  'game/third_party/googletest/src': Var('googletest_url') + '@' + Var('googletest_revision'),
  'game/third_party/icu': Var('icu_url') + '@' + Var('icu_revision'),
  'game/third_party/jinja2': Var('jinja2_url') + '@' + Var('jinja2_revision'),
  'game/third_party/markupsafe': Var('markupsafe_url') + '@' + Var('markupsafe_revision'),
  'game/third_party/zlib': Var('zlib_url') + '@' + Var('zlib_revision'),
  'game/third_party/v8': Var('v8_url') + '@' +  Var('v8_revision'),
  'game/tools/clang': Var('clang_url') + '@' + Var('clang_revision'),
  'game/buildtools/linux64': {
    'packages': [
      {
        'package': 'gn/gn/linux-amd64',
        'version': Var('gn_version'),
      }
    ],
    'dep_type': 'cipd',
    'condition': 'host_os == "linux"',
  },
  'game/buildtools/mac': {
    'packages': [
      {
        'package': 'gn/gn/mac-amd64',
        'version': Var('gn_version'),
      }
    ],
    'dep_type': 'cipd',
    'condition': 'host_os == "mac"',
  },
  'game/buildtools/win': {
    'packages': [
      {
        'package': 'gn/gn/windows-amd64',
        'version': Var('gn_version'),
      }
    ],
    'dep_type': 'cipd',
    'condition': 'host_os == "win"',
  },
  # GaME dependencies
  'game/third_party/glfw': Var('glfw_url') + '@' + Var('glfw_revision'),
  'game/third_party/glm': Var('glm_url') + '@' + Var('glm_revision'),
  'game/third_party/imgui': Var('imgui_url') + '@' + Var('imgui_revision'),
  'game/third_party/pugixml': Var('pugixml_url') + '@' + Var('pugixml_revision'),
  'game/third_party/stb': Var('stb_url') + '@' + Var('stb_revision'),
  'game/third_party/vulkan_headers': Var('vulkan_headers_url') + '@' + Var('vulkan_headers_revision'),
}

hooks = [
  {
    # Update the Windows toolchain if necessary.
    'name': 'win_toolchain',
    'pattern': '.',
    'condition': 'checkout_win',
    'action': ['python', 'game/build/vs_toolchain.py', 'update'],
  },
  {
    # Update the Mac toolchain if necessary.
    'name': 'mac_toolchain',
    'pattern': '.',
    'condition': 'checkout_mac',
    'action': ['python', 'game/build/mac_toolchain.py'],
  },
  {
    'name': 'clang',
    'pattern': '.',
    'action': ['python', 'game/tools/clang/scripts/update.py'],
  },
  {
    # Update LASTCHANGE.
    'name': 'lastchange',
    'pattern': '.',
    'action': ['python', 'game/build/util/lastchange.py',
               '-o', 'game/build/util/LASTCHANGE'],
  },
  {
    'name': 'sysroot_x64',
    'pattern': '.',
    'condition': 'checkout_linux and checkout_x64',
    'action': ['python',
               'game/build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=x64'],
  },
]
