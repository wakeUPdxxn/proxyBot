echo "Debug or Release?"
select choise in D R
do
    case $REPLY in
        D) mkdir build; 
	      cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Debug;
	      cmake --build build/debug;
	      break;;
        R) mkdir build; 
	      cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Release;
	      cmake --build build/release;
          break;;	
		*)
        echo "Unknown symbol $REPLY";
		break;;
    esac
done
