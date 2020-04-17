#Establece la versión mínima requerida para usar CMake
cmake_minimum_required(VERSION 3.10..3.17)

#Detalles del projecto

project ( Banco
	  VERSION 1.0.0
	  DESCRIPTION "App del banco de las Islas Caiman"
	  LANGUAGES C
	)

#Si queremos trabajar con C11, lo hacemos con...

set(CMAKE_C_STANDARD 11)

#Hacemos una opción interactiva

option(BUILD_DOCUMENTATION "Crear e instalar la API basada en HTML de documentacion (Obvio que requiere Doxygen)" OFF)
if(BUILD_DOCUMENTATION)
	find_package(Doxygen)
if (DOXYGEN_FOUND)
	set(DOXYGEN_HAVE_DOT YES)
	set(DOXYGEN_OUTPUT_DIRECTORY        ${CMAKE_CURRENT_SOURCE_DIR}/doc) 
	set(DOXYGEN_GENERATE_LATEX          NO)
	set(DOXYGEN_EXTRACT_ALL		    YES)
	set(DOXYGEN_EXTRACT_PRIVATE         YES)
	set(DOXYGEN_EXTRACT_PACKAGE         YES)
	set(DOXYGEN_EXTRACT_STATIC          YES)
	set(DOXYGEN_WARN_NO_PARAMDOC        YES)
	set(DOXYGEN_HTML_OUTPUT             doc_html)
	set(DOXYGEN_USE_MDFILE_AS_MAINPAGE  README.md)
	set(DOXYGEN_FILE_PATTERNS           *.c *.cc *.cxx *.cpp *.c++ *.ii *.ixx *.ipp *.i++ *.inl *.h *.hh *.hxx *.hpp *.h++ *.inc README.md)

	doxygen_add_docs(doxygen . WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
endif()
#La siguiente opción es simple, pero no es la mejor, puesto que es recomendable listar de manera explícita
#todo archivo header o source a usar en el proyecto.

file(GLOB sources "src/*.c")
file(GLOB headers "inc/*.h")

#Añadimos el nombre del ejecutable que nuestra build tool va a generar...
add_executable(banco ${sources} ${headers})

#CMake necesita de este archivo para linkear de manera correcta la librería, debe ser creado previamente...
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#Vamos a usar una base de datos, por tal motivo...
find_package (SQLite3)
#Incluimos los directorios y le decimos que los vamos a usar con el proyecto
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (banco ${SQLite3_LIBRARIES})
