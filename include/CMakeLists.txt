file(GLOB_RECURSE list_h list/*.h list/*.hpp)
set(LIST_H "${list_h}" PARENT_SCOPE)

file(GLOB_RECURSE polinom_h polinom/*.h polinom/*.hpp)
set(POLINOM_H "${polinom_h}" PARENT_SCOPE)

file(GLOB_RECURSE stack_h stack/*.h stack/*.hpp)
set(STACK_H "${stack_h}" PARENT_SCOPE)

file(GLOB_RECURSE table_h table/*.h table/*.hpp)
set(TABLE_H "${table_h}" PARENT_SCOPE)