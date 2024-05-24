file(REMOVE_RECURSE
  "../../lib/libextnum.a"
  "../../lib/libextnum.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/extnum.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
