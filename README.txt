Linguagens de Programacao - Exercicio Avaliado 02
Professor: Miguel Campista
Aluno: Daniel Becker Endres Mendonca 
DRE: 112093743




                INTRODUCAO
        
    Este programa visa implementar um gerador de grafos de um texto com output em forma de texto. 
Usando conceitos de programacao orientada a objetos foram implementadas classes que modelam Vertices, Arestas e "Super Arestas" de um grafo.
"Super Arestas" sao arestas que podem ser de ordem maior. Com essa implementacao de SA, as arestas como classe separada se tornaram obsoletas
e poderiam ser englobadas na classe das SuperArestas, mas isso tera de ficar para uma futura limpeza do codigo. 
    O codigo tem alguns comentarios ao longo dele, em especial nas classes que pertencem ao arquivo grafo.h, onde julgo estar o "grosso" do trabalho.
Esta classe trata da modelagem e implementacao das abstracoes que tornam o grafo possivel. Antes de chegarmos ao grafo as funcoes que se encontram 
definidas em processadorTexto.h fazem a limpeza e parsing do texto para que ele possa ser processado e tornado grafo. O arquivo estatisticas.h, apesar 
do nome elegante implementa iteradores de vetores e contadores que nos ajudam a extrair significado do grafo gerado. O paragrafo de texto encontra-se em
texto.txt que, para o bom funcionamento do programa, nao deve ter seu nome alterado. 


                COMPILACAO E LINKEDICAO

    Para que o programa possa ser compilado eh necessario que todos os arquvivos fonte referentes ao programa estejam no mesmo diretorio onde o arquivo makefile
se encontrar. Eh possivel compilar o programa sem o arquivo texto.txt, mas o mesmo nao executara corretamente sem ele. A compilacao e linkedicao sao automatizados,
bastando executar o comando make no diretorio onde os arquvivos fonte do programa se encontram. Apos a compilacao e linkedicao, os arquviso .o referentes aa montagem 
do programa podem ser removidos com o comando make clean. O compilador emite um aviso de variavel nao utilizada. Nao consegui remover o aviso e ainda discordo do 
compilador, mas este aviso nao deve atrapalhar em nada a montagem e execucao do programa.


                INSTRUCOES DE USO

    Uma vez feita a compilacao, basta executar o comando ./mainProgram no mesmo diretorio onde estao os outros arquviso do programa para inicia-lo. Todas as instrucoes
necessarias para a utilizacao dos recursos do programa sao aprensentadas durante a execucao e toda a interacao com o usuario eh feita atraves do teclado numerico. 


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------