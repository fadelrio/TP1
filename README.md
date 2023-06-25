# TP1
Introducción
Objetivo

El objetivo del presente trabajo práctico es implementar una versión simplificada del juego Poly Bridge de simulación de puentes, realizando para ello una simulación de sistemas masa-resorte y utilizando la biblioteca gráfica SDL2.

El trabajo consiste en la resolución de un problema mediante el diseño y uso de TDAs y en la reutilización de algunos de los tipos, funciones y conceptos desarrollados a lo largo del curso en trabajos anteriores.
Alcances

Mediante el presente TP se busca que el estudiante adquiera y aplique conocimientos sobre los siguientes temas:

    Encapsulamiento en TDAs,

    Contenedores y tablas de búsqueda,

    Punteros a funciones,

    Archivos,

    Modularización,

    Técnicas de abstracción,

además de los temas ya evaluados en trabajos anteriores.

Nota

Este trabajo es un trabajo integrador de final de cursada. En el mismo se van a aplicar todos los temas aprendidos y además se va a evaluar el diseño de la aplicación.

Es imprescindible entender los temas de TDA y modularización antes de empezar con el trabajo.

Es imprescindible diseñar el trabajo como etapa previa a la implementación.

Cualquier abordaje que pretenda empezar a codificar sin haber ordenado el trabajo primero está condenado a fracasar contra la complejidad del problema.
El juego

Se desea realizar un juego con dos etapas diferenciadas: La primera de ellas consiste en la construcción gráfica de la malla a utilizar, la segunda consiste en simular esta red y verificar si cumple las pautas de deformación máxima.
Malla

Durante la etapa de la construcción se debe interactuar con la malla, entonces previo a entrar en la dinámica hablemos de la malla.

La malla debe permitir garantizar las restricciones del juego y funcionar de forma más o menos eficiente para determinadas operaciones.

Las restricciones y operaciones son:

        Ningún resorte puede ser mayor a determinada longitud fija.

        Se debe poder buscar una masa dada una posición, la búsqueda será dentro de un radio con respecto a la posición.

        Se debe poder buscar un resorte dada una posición, la búsqueda será dentro de un radio con respecto a esa posición.

        Tanto los resortes como las masas tienen que poder ser eliminados. Ahora bien eliminar una masa implica que deben ser eliminados los resortes que la referencian.

        Las masas tienen que poder ser movidas. Ahora bien, siempre y cuando ese movimiento no rompa la longitud máxima. Pero, también hay masas que son fijas. Esas no pueden ser movidas.

        Al menos los resortes tienen que estar contenidos en una lista enlazada. Notar que los resortes sencillamente se recorren para todas las operaciones, por lo que no hay un orden ni acceso por índice.

Vamos un poco al diseño.

Como ya se sabe, este trabajo es sobre TDAs. Deben ser TDAs tanto los resortes, como las masas, como la malla.

El usuario Bárbara que utilice la malla puede conocer a los TDAs de los resortes y las masas. Es decir, tranquilamente una primitiva de búsqueda sobre la malla puede devolver el resorte o el nodo que corresponda.

Hay una operación recurrente que necesita ser resuelta en tiempo constante y es el recuperar las masas (y por ende sus coordenadas) asociadas a un resorte. (¿Por qué recurrente?, mirar las ecuaciones ya desarrolladas, todo el tiempo necesitamos aplicar a cada resorte sobre sus respectivos nodos u obtener la longitud de un resorte dado.)

Esto plantea un problema con múltiples soluciones, y termina siendo trasnversal al diseño de los tres TDAs. ¿El resorte guarda índices de masas?, ¿el resorte guarda punteros a las masas?, ¿las masas guardan su índice?, ¿pero si las masas guardan su índice entonces conocen de la existencia de la malla?, ¿las masas tienen índices?, ¿la malla no debería ser de más alto nivel que las masas?... ¿se entiende las preguntas? Son preguntas abiertas y son las preguntas que uno debería hacerse cuando diseña cualquier tipo del problema.

No hay una solución correcta. Hay criterios. Y los criterios tienen que estar debidamente justificados en la documentación de los TDAs. Un criterio puede estar mejor o peor, pero un TDA que no explicite los criterios está siempre mal, porque sin conocer qué se quiso resolver y por qué no se puede saber si la implementación es correcta.

Durante la fase de construcción el usuario tiene que poder crear una malla de forma interactiva.

A qué nos referimos con:

        Clickear: El usuario aprieta un botón del mouse y lo suelta en el mismo lugar.

        Arrastrar: El usuario aprieta un botón y sin soltar el mouse lo mueve, soltando el mouse en algún otro lugar.

Deben implementarse el siguiente comportamiento:

        Si se clickea sobre un lugar vacío se agrega una masa en ese lugar.

        Si se arrastra desde la posición de una masa se intenta mover dicha masa al lugar donde termine el arrastre.

        Si se clickea sobre una masa existente entonces se inicia el dibujado de un nuevo resorte que va a ir desde ese nodo hasta donde se haga click para finalizar. Si en el lugar de finalización hay una masa existente, el resorte va a ir de una masa a la otra, si no, se agregará una masa nueva.

        Si se hace click derecho sobre una masa, la misma se borra. A menos que sea una masa fija, esas no se pueden borrar.

        Si se hace click derecho sobre un resorte, el mismo se borra.

Notar que SDL informa de la acción de apretar el botón, mover el mouse o soltar el botón como eventos sueltos. Los conceptos de click y arrastre deben ser construidos en base a estos eventos de bajo nivel.

El juego consiste en diferentes "niveles".

Cada nivel empieza con dos masas fijas. En el primer nivel estas masas estarán a una distancia horizontal de 4 unidades entre una y la otra. Cada vez que se gane un nivel se empezará con una nueva malla, con una unidad más de distancia que el nivel anterior.

La simulación se animará en pantalla durante 10 segundos.

Al concluir esos 10 segundos se computará el porcentaje de estiramiento de cada resorte según

, si ese número llegara a ser mayor al máximo admitido para algún resorte entonces no se gana el nivel y se vuelve a la fase de construcción con la malla previa a la simulación.

En caso de que ningún resorte supere el umbral entonces se limpiará la malla y se iniciará un nuevo nivel, como se dijo, con los nodos fijos más alejados entre sí.

Para que sea un juego, tenemos que poder competir, ¿no? El puntaje se computará como la cantidad de resortes necesarios para pasar un nivel. Claramente menos puntos implica una mejor resolución.

¿Y cómo le muestro al mundo lo buena que fue mi resolución de un nivel? Al ganar cada nivel debe escribirse un archivo binario nivel_#.bin con la malla ganadora.

¿Y para qué me sirve ese binario?, si el programa se ejecuta recibiendo un archivo como parámetro, deberá simular esa malla.

¿Qué pasa si el usuario se aviva de que nuestro programa no se da cuenta de si realmente la malla une los dos nodos fijos?, cursá Algoritmos y Programación 2 el cuatrimestre que viene y después arreglalo. Todo no se puede.

Ya se dijo todo lo que había por decir.

El problema que se plantea en este trabajo deberá ser resuelto con las herrramientas ya adquiridas, extendiendo de forma consistente los TDAs ya planteados de ser necesario y diseñando los TDAs nuevos que hagan falta. Se evaluará además el correcto uso de los TDAs respetando la abstracción y el "modelo" de Alan-Bárbara, así como la separación de los cómputos físicos con respecto a la lógica de representación gráfica.

Se pide diseñar una aplicación que pueda ser ejecutada como:

$ ./monobridge <archivo.bin>

que permita jugar al juego que describimos con toda la lógica que se mencionó. El archivo es opcional, en caso de recibirlo se procederá como ya se explicó.

Se deben implementar TDAs donde se considere que es necesario.

Al menos los Resortes, Masas, Malla y Simulador tienen que ser implementados como TDAs con sus características y comportamiento.

El alcance es lo especificado en este enunciado. En cualquier aplicación amplia como esta siempre pueden implementarse detalles adicionales, los mismos no forman parte del enunciado y no hay que hacer nada adicional para alcanzar la máxima nota. La prioridad es resolver completa la funcionalidad descrita para terminar con eso la materia.
