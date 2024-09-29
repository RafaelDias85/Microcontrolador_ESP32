# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp-idf-config/v5.1.4/esp-idf/components/bootloader/subproject"
  "C:/RafaelDias/Microcontroladores/LinguagemC_focoMicrocontroladores/Projetos_C_SDK_IDF/EX03/build/bootloader"
  "C:/RafaelDias/Microcontroladores/LinguagemC_focoMicrocontroladores/Projetos_C_SDK_IDF/EX03/build/bootloader-prefix"
  "C:/RafaelDias/Microcontroladores/LinguagemC_focoMicrocontroladores/Projetos_C_SDK_IDF/EX03/build/bootloader-prefix/tmp"
  "C:/RafaelDias/Microcontroladores/LinguagemC_focoMicrocontroladores/Projetos_C_SDK_IDF/EX03/build/bootloader-prefix/src/bootloader-stamp"
  "C:/RafaelDias/Microcontroladores/LinguagemC_focoMicrocontroladores/Projetos_C_SDK_IDF/EX03/build/bootloader-prefix/src"
  "C:/RafaelDias/Microcontroladores/LinguagemC_focoMicrocontroladores/Projetos_C_SDK_IDF/EX03/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/RafaelDias/Microcontroladores/LinguagemC_focoMicrocontroladores/Projetos_C_SDK_IDF/EX03/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/RafaelDias/Microcontroladores/LinguagemC_focoMicrocontroladores/Projetos_C_SDK_IDF/EX03/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
