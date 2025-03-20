cmake_minimum_required(VERSION 3.4)

project(Program)

#Ustaw we własnej zmiennej SOURCE_FILES zbiór plików źródłowych projektu
set(SOURCE_FILES src/main.cpp ../library/src/model/Square.cpp ../library/include/model/Square.h ../library/exceptions/PieceException.h ../library/src/model/Player.cpp ../library/include/model/Player.h ../library/src/model/Knight.cpp ../library/include/model/Knight.h ../library/include/model/PieceFactory.h ../library/src/model/PawnFactory.cpp ../library/include/model/PawnFactory.h ../library/src/model/KnightFactory.cpp ../library/include/model/KnightFactory.h ../library/src/model/BishopFactory.cpp ../library/include/model/BishopFactory.h ../library/src/model/RookFactory.cpp ../library/include/model/RookFactory.h)

#Włącz powyższy zbiór plików do zbudowania programu wykonywalnego Program
add_executable(Program ${SOURCE_FILES})
#Określenie zależności pomiędzy projektami Program i Biblioteka
target_link_libraries(Program Library)
#Dołącz katalog include podprojektu Program do globalnej listy. Dzięki temu każdy inny podprojekt będzie ten katalog "widział"
target_include_directories(Program PUBLIC include)
enable_testing()
