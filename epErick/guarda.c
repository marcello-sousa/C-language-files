/*	p = procura_patio(l, p); */
			
			while (p != NULL) {
				
					if ((p->iden_patio == r->ident_rec[0] || r->uso_rec != 1) && (p->iden_patio == r->ident_rec[1] || r->uso_rec != 1)) {
						printf ("\nCiclo: %d, Navio: %s, Recuperadora %s, patio: %c \n", ciclo, l->nome_navio, r->nome_rec, p->iden_patio);
						r->uso_rec = 1;
						p->capacidade = p->capacidade - l->carga_navio;
						break;										}
					
					else break;		
				p = p->prox;
			}			
	   if (p == NULL) {
	      printf("Patio Lotado"); 
	      p = pa;
	     }      
		 
		}
