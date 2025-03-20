cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        src/model/Bishop.cpp
        src/model/Board.cpp
        src/model/ComputerPlayer.cpp
        src/model/Game.cpp
        src/model/HumanPlayer.cpp
        src/model/King.cpp
        src/model/Move.cpp
        src/model/Pawn.cpp
        src/model/Piece.cpp
        src/model/Queen.cpp
        src/model/Result.cpp
        src/model/Rook.cpp
        #Pliki Naglowkowe
        include/model/Bishop.h
        include/model/Board.h
        include/model/ComputerPlayer.h
        include/model/Game.h
        include/model/HumanPlayer.h
        include/model/King.h
        include/model/Move.h
        include/model/MovesList.h
        include/model/Pawn.h
        include/model/Piece.h
        include/model/Queen.h
        include/model/Rook.h
        #Repozytoria
        include/typedefs.h
        #Testy
        LibraryTest/BoardTest.cpp
        LibraryTest/master.cpp
        LibraryTest/MoveTest.cpp
        LibraryTest/PlayerTest.cpp
        LibraryTest/PiecesTest.cpp
        src/model/Square.cpp include/model/Square.h exceptions/PieceException.h src/model/Player.cpp include/model/Player.h src/model/Knight.cpp include/model/Knight.h include/model/PieceFactory.h src/model/PawnFactory.cpp include/model/PawnFactory.h src/model/KnightFactory.cpp include/model/KnightFactory.h src/model/BishopFactory.cpp include/model/BishopFactory.h src/model/RookFactory.cpp include/model/RookFactory.h)
#Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES} )

target_include_directories(Library PUBLIC include)
enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        LibraryTest/master.cpp
        LibraryTest/BoardTest.cpp
        LibraryTest/MoveTest.cpp
        LibraryTest/PiecesTest.cpp
        LibraryTest/PlayerTest.cpp LibraryTest/PawnTest.cpp LibraryTest/SquaresTest.cpp LibraryTest/KnightTest.cpp LibraryTest/BishopTest.cpp LibraryTest/RookTest.cpp LibraryTest/QueenTest.cpp LibraryTest/KingTest.cpp LibraryTest/ComputerPlayerTest.cpp) # tu w przyszłości będą dodawane pliki źródłowe testów

add_executable (LibraryTest ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
        add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
