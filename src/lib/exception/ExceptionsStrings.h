/*
 * ExceptionsStrings.h
 *
 *  Created on: 19 de ago de 2020
 *      Author: lhlag
 */

#ifndef LIB_EXCEPTION_EXCEPTIONSSTRINGS_H_
#define LIB_EXCEPTION_EXCEPTIONSSTRINGS_H_

	#include <string>

	static const std::string _INTERNAL_ERRO_INVALID_FUNCIONALITY = "Erro interno da máquina virtua. Funcionalidade inválida!";

	static const std::string _OVERLOAD_CODE = "Fim do código encontrado em local invalido!";

	static const std::string _LOAD_CONTEXT_NOT_VALID_STR = "Erro ao tentar criar um Context inválido!";

	static const std::string _CREATE_FUNCTION_JIT_STR = "Erro ao criar função jit!";
	static const std::string _ERROR_JIT_CREATE_NOT_FOUND_REGISTER_TYPE = "Erro ao criar um jit em tempo de execução, tipo ou tamanho de registrador não encontrado!";
	static const std::string _ERROR_JIT_CREATE_ANY_REGISTER_FREE = "Erro ao criar um jit em tempo de execução, nenhum registrador livre para uso encontravel!";
	static const std::string _ERROR_JIT_CREATE_ANY_COMAND_FOUND = "Erro ao criar um jit em tempo de execução, nenhum comando equivalente encontrado depois da pré verificação!";
	static const std::string _ERROR_JIT_CREATE_ASMJIT_RETURN_ERROR = "Erro ao criar um jit em tempo de execução, biblioteca asmjit não conseguiu criar memória executavel!";
	static const std::string _ERROR_JIT_CREATE_PRE_JIT_NOT_FOUND = "Erro ao criar um jit em tempo de execução, nenhum comando equivalente encontrado na pré verificação!";


#endif /* LIB_EXCEPTION_EXCEPTIONSSTRINGS_H_ */
