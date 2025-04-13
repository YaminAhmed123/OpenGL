file(REMOVE_RECURSE
  "RenderEngineExecutable"
  "RenderEngineExecutable.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/RenderEngineExecutable.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
