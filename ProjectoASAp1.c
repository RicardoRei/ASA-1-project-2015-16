#include <stdio.h>
#include <stdlib.h>


typedef struct node* link;
typedef struct Vertex* item; /* para facilitar a leitura de ponteiros para a estrutura vertex e node*/

/*
*@brief Vertex
* 		estrutura que vai guardar informacao relatica a um vertice.
*/
struct Vertex
{
	int id;
	int visited;
	item pi;
	int d;
	int low;
	int articulation;
};

struct node
{
	item _vertex;
	link next;
};

typedef struct
{
	link head;
	link tail;
} Queue;

/*
*@brief struct Graph:
*		estrutura que contem uma lista de adjacencias, um inteiro com o numero de vertices, o vertice que representa
*		o Paul, e o vector com todos os vertices.
*/
typedef struct
{
	link* adjacenciesList;
	int verticesNumber;
	item _paul;
	item* _vertices;

}Graph;

//Graph DFSsearch(Graph graph);
//void DFSvisit(item u, Graph* graph);
Graph algorithm(Graph graph);
void visit(Graph* graph, item u);
item createVertex(int i);
Graph builtGraph();
void outPut(Graph graph);
void printGraph(Graph graph);
int min(int a, int b);
link createNode(item i);
link insertLinkedList(item i, link head);

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int time = 0;
int main()
{
	Graph graph = builtGraph();
	graph = algorithm(graph);
	outPut(graph);

	return EXIT_SUCCESS;
}

void outPut(Graph graph)
{
	int i, count = 0;
	int m = graph.verticesNumber;
	int M = -1;

	for (i = 0; i < graph.verticesNumber; i++)
	{
		if (graph._vertices[i]->articulation == 1)
		{
			if (graph._vertices[i]->id < m)
				m = graph._vertices[i]->id;

			if (graph._vertices[i]->id > M)
				M = graph._vertices[i]->id;

			count++;
		}
	}

	if (count == 0)
	{
		m = -2;
		M = -2;
	}
	
	printf("%d\n", count);
	printf("%d %d\n", ++m, ++M);
}

void visit(Graph* graph, item u)
{
	link current = graph->adjacenciesList[u->id];
	int children = 0;
	u->visited = 1;
	u->d = u->low = ++time;

	while (current != NULL)
	{
		if (current->_vertex->visited == 0)
		{
			children++;
			current->_vertex->pi = u;
			visit(graph, current->_vertex);
			u->low = min(u->low, current->_vertex->low);
			if ((u->pi == NULL) && (children > 1))
			{
				u->articulation = 1;
			}

			if ((u->pi != NULL) && (current->_vertex->low >= u->d))
			{
				u->articulation = 1;
			}
		}
		else if (u->pi == NULL)
			u->low = min(u->low, current->_vertex->d);

		else if (current->_vertex->id != u->pi->id)
		{
			u->low = min(u->low, current->_vertex->d);
		}
		current =  current->next;
	}
}

Graph algorithm(Graph graph)
{
	int i;
	for (i =  0; i < graph.verticesNumber; i++)
	{

		if (graph._vertices[i]->visited == 0)
		{
			visit(&graph, graph._vertices[i]);
		}
	}
	return graph;
}

/*
*@brief createVertex;
*		Funcao que cria um vertice inicialmente com o valor pi (previous) a NULL, d (distancia a paul) a -1, e a color a 0 (branco)
*/
item createVertex(int i)
{
	item new = (item)malloc(sizeof(struct Vertex));
	new->id = i;
	new->pi = NULL;
	new->d = -1;
	new->visited = 0;
	new->low = 0;
	new->articulation = 0; 
	return new;
}

/*
*@brief builtGraph;
*		Le do standard input o numero de vertices e arestas, o numero do vertice que representa o paul e as transicoes/arestas.
*		Constroi o grafo com essa informacao.
*		
*/
Graph builtGraph()
{
	int vertices, edges, vertexOne, vertexTwo, i;

	Graph graph;

	scanf("%d %d", &vertices, &edges);
	graph.adjacenciesList = (link*) malloc(sizeof(link)*vertices);
	graph.verticesNumber = vertices;
	graph._vertices = (item*) malloc(sizeof(item)*vertices);

	for ( i = 0; i < vertices; i++)
	{
		graph.adjacenciesList[i] = NULL;
		graph._vertices[i] = createVertex(i);
	}

	for (i = 0; i < edges; i++)
	{
		scanf("%d %d", &vertexOne, &vertexTwo);
		graph.adjacenciesList[vertexOne-1] = insertLinkedList(graph._vertices[vertexTwo-1], graph.adjacenciesList[vertexOne-1]);
		graph.adjacenciesList[vertexTwo-1] = insertLinkedList(graph._vertices[vertexOne-1], graph.adjacenciesList[vertexTwo-1]);
		
	}
	return graph;
}


/*
*@brief createNode:
*		cria um no atraves de um vertice.
*/
link createNode(item i)
{
	link new = (link) malloc(sizeof(struct node));
	new->_vertex = i;
	new->next = NULL;
	return new;
}

/*
*@brief insertLinkedList:
*		insere um elemento no inicio da lista.
*/
link insertLinkedList(item i, link head)
{
	link new = createNode(i);
	if (head == NULL)
		head = new;
	else
	{
		new->next = head;
		head = new;
	}
	return head;
}
