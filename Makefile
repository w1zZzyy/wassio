impl-build-%:
	@mkdir -p build_$*
	@cd build_$* && cmake -DCMAKE_BUILD_TYPE=$* ..
	@cmake --build build_$*

impl-test-%: impl-build-%
	@cd build_$*/tests && ctest

build-debug build-release: build-%: impl-build-%
test-debug test-release: test-%: impl-test-%