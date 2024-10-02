echo "Debug or Release [D] or [R]?"
select choise in "D" "R"; do
    case $choise in
        D ) mkdir build; 
	      cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Debug;
	      cmake --build build/debug;
	      cmake --install . --prefix "../../bin"
	      break;;
        R ) mkdir build; 
	      cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Release;
	      cmake --build build/release;
	      cmake --install . --prefix "../../bin";
          break;;
    esac
done
