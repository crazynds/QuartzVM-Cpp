## [0.2.0] - 20-04-2021
### Added
 - JIT is now have official suport for the most of commands
 - Create template for customs commands in interpreted mode and JIT mode
 - Now the default lang used in all files is the en (English)
 - Now each virtual thread has its own thread via software and is executed separately (Start of parallelism :] !!)
### Changed
 - Context memory now is static in all program execution
 - Asmjit library is loaded direct by the git comunity
 - Increase modularization of all classes
 - Most of the variables of Thread and VM are now private
 - Increase speed of execution in all VM execution
### Removed
 - All static library of commands and other things
### Fix
 - Fixed all bugs that prevent normal code from running

## [0.1.1] - 17-06-2019
### Added
 - Atualização do wordcoder para utilização dinamica das chamadas das funções;
### Changed
### Removed

## [0.1.0] - 17-06-2019
### Added
 - Implementado Optimizacao no reaproveitamento dos registradores (RAX,RBX,RCX,RDX) para melhora de performance; (BETA)
 - Adicionado ponteiros avançados (REG1+REG2<<IMD+IMD);
 - Biblioteca Wordcoder modificada para se tornar dinamica;
 - Implementado header de código;
 - Implementado sistema de versões no código fonte e de VM. Implementado também sistemas da versão e de correção;
### Changed
 - Atualizado sistema de logs;
 - Repositorio agora esta livre no GitHub;
### Removed
 
## [0.0.3] - 22-05-2019
### Added
 - Implementado optimizacao JIT em comandos estaticos ao invez de utilizar a linguagem C++; (ALPHA)


## [0.0.2] - 04-05-2019
### Added
 - Implementa flags de optimizaÃ§Ã£o JIT; 


## [0.0.1] - 10-04-2019
### Added
 - Interpretada totalmente;
 - Optimizacao vetorial para acesso ao comando;
 
