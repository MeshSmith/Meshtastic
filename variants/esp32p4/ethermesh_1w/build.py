# trunk-ignore-all(ruff/F821)
# trunk-ignore-all(flake8/F821): PlatformIO supplies Import and env.
Import("env")


def firmware_only(build_env, node):
    # The SDK's dummy sketch cannot include Meshtastic application headers.
    return None if build_env.get("ARDUINO_LIB_COMPILE_FLAG") == "Build" else node


env.AddBuildMiddleware(firmware_only, "*ethermesh_1w*variant.cpp")
