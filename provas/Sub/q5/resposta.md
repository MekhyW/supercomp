As técnicas de otimização e métodos de paralelização discutidos em sala de aula são bem diferentes em proposta e aplicabilidade para resolver problemas computacionais complexos. Cada uma delas foca em um paradigma específico e uma camada de abstração específica, e pode ser mais ou menos adequada para diferentes tipos de problemas.

### Heurística, Pesquisa Local e Global

- **Heurísticas**: encontrar soluções aproximadas para problemas complexos. Frequentemente usados quando o problema é muito complexo para ser resolvido com exatidão ou quando a solução exata não é necessária.
- **Pesquisa Local**: busca pela melhor solução dentro de uma pequena vizinhança da solução atual. É bom para problemas com ótimos locais.
- **Pesquisa global**: busca pela melhor solução em todo o espaço de soluções, garantindo que a solução encontrada seja a melhor possível.

### Threads com OpenMP

- **OpenMP**: Modelo de programação paralela que permite aos desenvolvedores escrever código paralelo usando um modelo de memória compartilhada. Ele foi projetado para paralelismo multithread em arquiteturas de memória compartilhada.

OpenMP é útil para problemas que podem ser divididos em tarefas menores que podem ser executadas simultaneamente por vários threads. É particularmente eficaz para problemas com alta intensidade computacional e poucos requisitos de memória.

### Processos Multimáquina com MPI

- **MPI**: Protocolo de comunicação padronizado para computação paralela que permite aos desenvolvedores escrever código paralelo usando um modelo de memória distribuída. Ele foi projetado para paralelismo em várias máquinas ou nós.

Útil para problemas que exigem paralelismo massivo e podem ser divididos em tarefas menores que podem ser executadas simultaneamente por vários processos em várias máquinas. É particularmente eficaz para problemas com altos requisitos de memória e baixa intensidade computacional.

### Programação para GPU com CUDA e Thrust

- **CUDA**: Plataforma de computação paralela e modelo de programação desenvolvido pela NVIDIA que permite aos desenvolvedores escrever código paralelo para GPUs NVIDIA. Ele foi projetado para computação de uso geral em GPUs.
- **Thrust**: Biblioteca de algoritmos paralelos para CUDA que fornece abstrações de alto nível para algoritmos paralelos (para rodar em GPUs da NVIDIA especificamente).

CUDA e Thrust são úteis para problemas que podem ser paralelizados e executados com eficiência em GPUs. Eles são particularmente eficazes para problemas com alta intensidade computacional e poucos requisitos de memória.

### Comparação

- **Memória compartilhada vs memória distribuída**: OpenMP e CUDA/Thrust usam modelos de memória compartilhada, enquanto MPI usa um modelo de memória distribuída. Isso significa que OpenMP e CUDA/Thrust são melhores para problemas com alta intensidade computacional e baixos requisitos de memória, enquanto MPI é melhor para problemas com altos requisitos de memória e baixa intensidade computacional.
- **Multithreading vs Multiprocessing**: OpenMP é projetado para multithreading, enquanto MPI é projetado para multiprocessamento. Isso significa que OpenMP é melhor para problemas que podem ser divididos em tarefas menores que podem ser executadas simultaneamente por vários threads em uma única máquina, enquanto MPI é melhor para problemas que exigem paralelismo massivo e podem ser divididos em tarefas menores que podem ser executadas simultaneamente por vários processos em várias máquinas.
- **Métodos Heurísticos e de Pesquisa**: Esses métodos podem ser usados em conjunto com métodos de paralelização para encontrar boas soluções para problemas complexos. Métodos heurísticos e de busca podem ser usados para encontrar uma solução inicial e, em seguida, métodos de paralelização podem ser usados para melhorar.
