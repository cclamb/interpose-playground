# clang -dynamiclib -o libTest.A.dylib -Wl,-no_pie printer.c
# clang -o test -Wl,-no_pie test.c libTest.A.dylib

# After building, need to run ldld -S <exename> to codesign
CC=clang
OBJ=stack.o heap-stack.o function.o function2.o function3.o function4.o
SDK_HOME=SDKs
SDK=$(SDK_HOME)/iPhoneOS9.3.sdk
# SDK=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.0.sdk
NO_ASLR_FLAGS=-Wl,-no_pie
DEBUG_FLAGS=-g

# can we use -target arm64-apple-ios? arm64-apple-darwin does work
# Valid architectures seem to be arm64, armv7, and armv7s.
#
# Valid triples include:
# arm64-apple-darwin
# armv7-apple-darwin
# armv7s-apple-darwin
# arm64-apple-ios
# armv7-apple-ios
# armv7s-apple-ios
#
#	IMPORTANT: using arm64 as the target architecture will prohibit
# the linker from creating a non-ASLR executable!
#
# the arm64 target is equivalent to armv8 aarch64, while the arm7* target
# produces 32-bit code, but we can use with ASLR off.
IOS_TARGET=-target armv7s-apple-ios -isysroot $(SDK)
MACOS_TARGET=

ARGS = $(IOS_TARGET) $(DEBUG_FLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(ARGS)

main: $(OBJ)
	$(CC) -o stack stack.o $(ARGS) $(NO_ASLR_FLAGS)
	$(CC) -o function2 function2.o $(ARGS) $(NO_ASLR_FLAGS)
	$(CC) -o function function.o $(ARGS) $(NO_ASLR_FLAGS)
	$(CC) -o heap-stack heap-stack.o $(ARGS) $(NO_ASLR_FLAGS)
	$(CC) -o function3 function3.o $(ARGS) $(NO_ASLR_FLAGS)
	$(CC) -o function4 function4.o $(ARGS) $(NO_ASLR_FLAGS)

clean:
	rm *.o stack heap-stack function function2 function3 function4
	rm -rf *.dSYM
