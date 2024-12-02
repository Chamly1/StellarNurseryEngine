include_directories(include)

add_library(main_obj OBJECT
"cpp/main.cpp" "cpp/App.cpp" "cpp/VulkanUtils.cpp" "cpp/utils.cpp" "cpp/Window.cpp" "cpp/Pipeline.cpp")