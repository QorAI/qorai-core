solutions = [
  {
    "managed": False,
    "name": "src",
    "url": "https://chromium.googlesource.com/chromium/src.git",
    "custom_deps": {
      "src/testing/libfuzzer/fuzzers/wasm_corpus": None,
      "src/third_party/chromium-variations": None
    },
    "custom_vars": {
      "checkout_clang_coverage_tools": True,
      "checkout_pgo_profiles": False
    }
  },
  {
    "managed": False,
    "name": "src/qorai",
    "url": "https://github.com/qorai/qorai-core.git"
  }
]
