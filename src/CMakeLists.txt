include_directories(include)

add_library(main_obj OBJECT
"cpp/main.cpp" "cpp/App.cpp" "cpp/VulkanUtils.cpp" "cpp/utils.cpp" "cpp/Window.cpp" "cpp/Pipeline.cpp" "cpp/Device.cpp" "cpp/SwapChain.cpp" "cpp/Application.cpp" "cpp/Model.cpp")