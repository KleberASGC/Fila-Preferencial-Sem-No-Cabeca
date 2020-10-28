#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->idade = -1;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->ant;
	}
	printf("\n\n");
}


int consultarIdade(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, int idade){
	if(id < 0 || idade < 0) return false;
	if (buscarID(f,id)) return false;
	PONT novo = (PONT) malloc(sizeof(ELEMENTO));
	novo->id = id;
	novo->idade = idade;
	if(f->cabeca->prox == f->cabeca) {
	 	f->cabeca->prox = novo;
	 	f->cabeca->ant = novo;
		novo->ant = f->cabeca;
	 	novo->prox = f->cabeca;
	 	if (idade < IDADEPREFERENCIAL) f->inicioNaoPref = novo;
	 	return true;
	}	
	if (idade < IDADEPREFERENCIAL) {
		if (f->cabeca == f->inicioNaoPref) f->inicioNaoPref = novo;
		novo->ant = f->cabeca->ant;
		novo->prox = f->cabeca;
		f->cabeca->ant->prox = novo;
		f->cabeca->ant = novo;
		return true;
	}
		if(idade >= IDADEPREFERENCIAL) {
		novo->ant = f->inicioNaoPref->ant;
		novo->prox = f->inicioNaoPref;
		f->inicioNaoPref->ant->prox = novo;
		f->inicioNaoPref->ant = novo;
		return true;
	} 

	return false;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){
	 if(f->cabeca->prox == f->cabeca) return false;
	*id = f->cabeca->prox->id;
	PONT apagar;
	if (f->cabeca->prox == f->cabeca->ant) {
		apagar = f->cabeca->prox;
		f->cabeca->prox = f->cabeca;
		f->cabeca->ant = f->cabeca;
		f->inicioNaoPref = f->cabeca;
		free(apagar);
		return true;
	}
	if(f->cabeca->prox == f->inicioNaoPref) {
		apagar = f->cabeca->prox;
		f->cabeca->prox = apagar->prox;
		apagar->prox->ant = f->cabeca;
		f->inicioNaoPref = f->cabeca->prox;
		free(apagar);
		return true;
	}
	apagar = f->cabeca->prox;
	f->cabeca->prox = apagar->prox;
	apagar->prox->ant = f->cabeca;
	free(apagar);
	return true;
	
}


bool desistirDaFila(PFILA f, int id){
	if (!buscarID(f,id)) return false;
	PONT apagar = buscarID(f,id);
	if(f->cabeca->prox == apagar && f->cabeca->ant == apagar) {
		if (apagar == f->inicioNaoPref) f->inicioNaoPref = f->cabeca;
		f->cabeca->prox = f->cabeca;
		f->cabeca->ant = f->cabeca;
		free(apagar);
		return true;
	}
	if(apagar == f->cabeca->prox) {
		f->cabeca->prox = apagar->prox;
		apagar->prox->ant = f->cabeca;
		free(apagar);
		return true;
	}
	if(apagar == f->inicioNaoPref) {
		apagar->ant->prox = apagar->prox;
		apagar->prox->ant = apagar->ant;
		f->inicioNaoPref = apagar->prox;
		free(apagar);
		return true;
	}
	if(apagar == f->inicioNaoPref->ant) {
		apagar->ant->prox = f->inicioNaoPref;
		f->inicioNaoPref->ant = apagar->ant;
		free(apagar);
		return true;
		
	}
	apagar->ant->prox = apagar->prox;
	apagar->prox->ant = apagar->ant;
	free(apagar);
	return true;
}
