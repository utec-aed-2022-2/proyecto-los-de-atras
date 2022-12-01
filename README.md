# **Blockchain**

## **Introducción**

**¿Qué es Blockchain?**

Un Blockchain es una cadena secuencial e inmutable de registros 
llamada Blocks. Pueden contener transacciones, archivos o cualquier dato que desee. Pero 
lo importante es que están encadenados mediante hashes.

![structures](img/blockchain.jpg)

**¿Qué es SHA256?**

SHA-256 (Secure Hash Algorithm 256) es un algoritmo (o función) cuyo objetivo es generar hashes 
o códigos únicos con el que se pudieran asegurar documentos o datos informáticos frente a cualquier
agente externo que desee modificarlos. una de sus características es que la longitud del hash resultante es siempre igual, sin importar lo extenso que sea el contenido que uses para generar el hash (el resultado siempre es una cadena de 64 de letras y números).

![structures](img/sha256.png)

## **Objetivo**

Implementar un sistema informático transaccional que permita a un usuario del sistema registrar
operaciones de manera segura (Blockchain) para luego realizar búsquedas de manera eficiente
usando diversas estructuras de datos como mecanismos de indexación para diferentes criterios de búsqueda.

## **Propuesta**

**Dominio transaccional utilizado** : transferencias bancarias (emisor, receptor, monto, fecha)

**3 clases principales** :

![structures](img/main.png)

* **transaction** :

Esta clase acepta los siguientes tipos de datos: string, date y float. Ello se debe a la información que contiene esta clase (sender, receiver, amount y date) y que se puede ver de la siguiente forma en la interfaz gráfica la interfaz gráfica de la siguiente forma:

![structures](img/transactionUI.jpeg)

* **block** :

Esta clase contiene el id, nonce, prev hash y hash. Los dos primeros son de tipo unsigned long long (tambien conocido como uint64_t).Esta clase contiene el id, nonce, prev hash y hash. Los dos primeros son de tipo unsigned long long (tambien conocido como uint64_t).

* **blockchain** :

En esta clase se registra el usuario y la contraseña (ambos serian strings) para luego poder crear un bloque de transaccion a partir de la clase block. Por lo tanto, también aceptará los mismos tipos de datos de esta última.

## **¿Qué estructuras usamos?**

![structures](img/structures.jpg)

* **Hash** : Usamos esta estructura para:
    - indexar a los usuarios.
    - indexar las transacciones.
    - facilitar el acceso a un nodo de un double list.

* **Heap** : Usamos esta estructura para:
    - obtener el valor máximo (*maxheap*) y mínimo (*minheap*) dentro de un grupo de valores.
    - obtener los valores máximos (*maxheap*) y mínimos (*minheap*) dentro de un grupo de valores.

* **Double List** : Usamos esta estructura para:
    - facilitar el hash en cascada en la blockchain.

* **B Plus Tree** : Usamos esta estructura para:
    - indexar las transacciones (por fecha y por monto).
    - hacer búsquedas por rango (transacciones hechas entre los montos A y B, transacciones hechas entre las fechas A y B).
    - indexar las transacciones por nombre (el nombre del usuario que hizo la transacción).
    
## ** Diagrama de clases**

![structures](img/UML_proyecto.png)

- [Link directo](https://viewer.diagrams.net/?tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&title=UML%20proyecto%20#R7R3Zcts48lv2QVV2qpziJYl6tOwcs%2FZMvI6SzO6LCiYhiWOKUEgqluZhvn1xUiQBUiQlWnbCqsxYBBpnNxp9AeiZV8vNhxCsFr8jF%2Fo9Q3M3PfO6ZximMbDxH5KyZSmGbeksZR56LktLJXz2%2FoY8UeOpa8%2BFUQYwRsiPvVU20UFBAJ04kwbCED1lwWbIz7a6AnMoJXx2gC%2BnfvPceMFSbWO4S%2F8IvflCtKwPRixnCQQwH0m0AC56SiWZ73rmVYhQzH4tN1fQJ7Mn5uXbb9tv%2Fu3j4MO%2F%2FxN9B1%2FGN5M%2Fvl6wyt7XKZIMIYRB3LjqR8P9%2FOeVt%2Fm23P64%2FaJ%2FH3%2B7%2BX5hW3xs8VZMGHTx%2FPFPFMYLNEcB8N%2FtUschWgcuJNVq%2BGsHc4vQCifqOPEvGMdbTgxgHSOctIiXPs%2FFwwi3f5KPt5pmiYT%2Fkgrf6sME4nrDm2Bf2%2FTXHQy9JYxhmCS6l4Ra8OeDj5xHlvTe830OwMZJBpejiz2TyuEitA4dWDKTnEhiEM5hXAJnmQnp4EUHER5EuMUFQ%2BiD2PuR7R3gxD9P4HYIxj84jmvgm%2FfyB%2FDXvKXxKg4hlKggevKWPggIumcoiAVBENwA35sH%2BLeDJ47M%2F%2FgHDGMPr7hLnhETMhg7C893b8EWrcl0RDFwHsXXeIFC729cLRAUgbPDmNOLMchAfCYlORJDGGGYO4EzPZf0O9hkAG9BFPMEB%2Fk%2BWEXeQzKMJcaUF4xRHKMlB5phcrlCPgrpHJgz24GOQ3sXokeYynmw%2B1Z%2FR1VkAuCmAV3JZCBqMUYcVZzvDvnn046HmYIxLVL8yxJ89%2Biko0ukc0HIlrK%2FS%2FwrwHtHzxj4BL8T%2FGNOfrzBP%2FB86WSuLihT3VC6wJPDShE0TeMclA%2BjiGXP1oETeygQFT%2FgreMMbxUYr4ZGWgHLFUXDFdtCcunnoh%2B5BuYhBJR2L3tXRu%2ByrWbg9zWh8KM3klurmPbiUiotomuxkn04iwvXcbQCjhfMbynMtbVLuedUR5IQLjvzKftdeK5LsIu3iRjEgC040osV8oKYUmV%2FjP9hOr3S3vZ7%2FWsy4v5Y333jfwQ8jK%2FILITAoysJ4tX8BKO46rIrZoDyshPSzaDaKhPb5tEXmSEtMgnbvke5MsO2EGn05lheYnzRbZ2jdUI38QtdQr0po95UoNkHD9C%2FQ5FHad28DhlsDv37MHwgy22Ae12vyGLtlnBvKnCPR6uN7%2Fx1NMGb9Nl5ir%2BwvH9oZqzO3BUUXDbNf%2BvCM75EWTP9JXgo%2FaCcTq7RCyKMpzPMxLRHuD1nPP0HwtOQh4wgCJ1FDpJwSAnyA4zv8aZzdl5x22Glll4gSkzkTLApy3yEt17EG6Sc%2FBqtMb2TRKnlwuL3IJhDOj4q67BpI59YTG1W88wL3Cn%2BD27OJm%2BYtrSrFU8i%2B0hQ6ROU0zGSxaasjMzlWdGE8plONVAPA14Ml1NBELX6O5Ero0QpalN34I0AuxTtFI6MgsnNsxQ6Wxqd59IBF3YyNe4Kc1ulk%2Bn5p2RTAwu0I%2Fdt9KR0ZbdLW8kaLe7zOowQp4PyRSakMM3HAGUDc3w8svIhZYp3UltrO7ddbec2RkZLe%2FfgRHaUxOjhemCJAney8IJe3vSRJ6QZHKjVWnc4etCew1hiVTSWMPH3AGMJLYrnCGxTAJykdzXfIcbkBVXiBZhRvm0rZ1rLF7D00gL4B%2BvDjsCSwTSnOUuSFwnL8Slb66w5zcm%2BBWsOYegZ%2BlCYc%2FSRgmPpVlvmnL7SnONi3o%2F%2FyLIwyQzojlXZ1rMK4Y9y8Io7YoKfIoz%2BgjuiVdeOoSSvflt2jMER7RgVsfxK7Bj1mE0D3NsVWUtbZoxhgRmDKgAKC0ZBOk2eJCypVCEhjOm8YyftkZQsX6vZSVvi9XBwYvFa7VPMEZALoD1TShgDx4YPs2cQrO2qgvXwQMH6IHTaSsl1AaJFJ7keQlfHl1yHWlax0VWOSLXkqre1wYyUkiv7TETXrzlhlNgXWc5N5Y0imd0ifPyCG4V9FLnTbEvu1OUAh8aCZ1U0vxLBsx6vaID8wYkFT12OUDhA8rzppZwS9IvWW13M7LhHbQKqKma2ZhMZnUbMFNFwvUwknKZbvdcYCaebFYXQAtHjeWRQXXa3k4X%2F0IXDvcRwOGFQTwSNflUx1C7Zbnh799CJQTD34a5BS8u2Z6na01WSTY43AR8TRQBiOCZsIpLI9gh%2BAF12BBCJ14umPgQzZSRF9VC8iBJhYTY1zshOepKVrXy%2Fz%2FwiRSZHMBp3btQinnew9K5rrYnvsleisfjexb%2FVRL9unlqAV3kNmgrwBSFvHfdoj3xOLb4LBfSFWYlbl7dHFeXtQ0%2BeNAumyMdG9I09wRQDUzusgGk%2BQ%2FSFrXfEVupROg21acMc8fT3EE%2B%2BgMEt3q0Sjy7bsNNBiZ3y%2BaKid0wzx8GE%2BTq90w0UO13iiz%2F%2BORHZzk30p1mI9qlPGX3rgaKzMniJMlhZsuq870XsoJZepiK31qJ5DJVlvala1oXz1MO%2BKp5Hhf22tDKBa0kre3%2F%2F6Y9J8bmZ8eXVTXHuah0tppRdJUE%2BZbH2FJxwq2rQaMXr3gdFqywD8qIpXK7i7VnZkSR2EqCsmgc43x1AqnioAQt2NUukjlvtoqaYuLNCUWH%2F0AqGIMYU3SeV4EVwli%2BTPp2aa%2FPzb%2F97J7opdoVuK2iNGSh0bBUz0Fs76WCbp9F7uI9Me2uZw17KT0aukDB6r9FPJq4geaGq1GCQVYx0fY8eni9gDcrh7b5dBt%2BO5mXI4akfu7gztc510rizHPFpCuO0oak4X3s6lxy2SJQiwIiU7H%2FywcLMxn2DdxAamCaOGiqVLAeQ7Sve1nHKsUOg8v%2Br7sRdrEr1ENlipUxJj%2B0pZbINqbFS1oW61cS%2BQilTYr%2B1uyJUcY5EHCebmcpVVpBOkxNXmWA9MlwE43xI3FfRfJneM0%2BVO1eE5mYvf8gCMlWr42Ct0bCsSyhpuD1VQmZYz6tKDC3r51AlTHGz4stUJUZ6TjMYlWsGI3HHpBq%2BHc3AlI2cHyFYdZqBQjOAutuHQxUfHg2GJhi0qRnk%2FHUDQ7EV2wo2ZrYWd2DKFlIipV8WBcY1EPC7%2B%2FEaNVJZfEjItojQf0HxwSxYiCUKkGrdjdpSgEzVhWkNFaCqeH4lClA9LtwE%2B3pVttuaBiRHPXOVBm%2FaSg1InU6TK2hAargml%2BIRX1aVK%2FFWaFXqU4p3%2BbJ%2FDWeyG%2BfOi0xTxRfL7Xd43V3ev%2FtjciZfjaa6Wu723fuqoPe%2FffhYFVaM8D4NX%2BuCL1cvm94FRrg3216jp0DRo7IiX1aFBbrtqD2GpFBnVQzJENvE8eNPT%2B0aM4ZmL3OEbDQataLPVg7Ouh6Oxs9yo5gI0Wr%2FSrHDdi35gEMX8vcCQ%2F70XEix6sIuQ3nFYP4A2PFIR3WxTkNxtwvCUi%2FMWsrOs94NLfsec0FYZH6pnOGFMdGqy0KyqsCqA7TyJaniXj1iq0bxdAhXvWIipqt6qXSQl7JUedRX9YaSMDBlkXpxYXWq4N7guuFiFQdWHj9GK8lS2p5QMpk8u8Cyw8XncganCGlXMjh9NGiJxQ3lcIXnPVDj%2BCCKPCcj7BIQF0QL2oT%2BDHKsOOe%2B35NTcJfG88ixI5X%2Fma9rP6Nn069Z6OE5TdKymrj6URMyxbdEXMjia6%2F0m4gsVAYtXIXXZYuJv0XGC%2FeShbB3kQ0LLqrm1WMNzbK4GFfP47ZzkQkQNJtFMJYQeYx7hRWPRFEtsFNS5C0FCxu2a6o2IcxSrb7bopIyzN2JcSFurU7z8KGChwt36vHZgiV7whrrKMnM%2Fhw6Sj1yKFmYtXQUFfrb0lEs2R9zwcsQaW6N52hgSb7MAAUOLIXY3TEi23Xx1AcRoG7DNwVORlKchvjSKliwLyuMcYRpgYm9FSpCoQvD8fYaxLy%2FyXs5NXrDK7lcYsElbl7NEmwmm11PWKBC9dJeUK00mxlyryKvJ69IJH1JD6hJb6qVl%2Foj3zi%2BQ7VAbwZkUZ5NzZ0ZLxFJ%2FUedzFJ3VEtInT0iw6tOOqQuyWyrRLjgkhCKFzDMwybalXldWIJ5alimrF1d7HS97HRqcYE7g8YgsKC8ohKqG4UwZy%2FwWLG4B99ZY6EH8ljEYiykhpwedWawcvOi1L8alBHkJv6eIfKoFlgSEO7aEzU%2B8NqETKsloJmaPz1ssZCzeziqIffC1Vwepxremz1ewVpdOrwuxscOq4Iys8N7cXl4L2pXUdGekcgODUWkn9GesUcYUtkzlLJwvzV7xmkvk9Tkp5VN63U%2BrWxVfS7otG8ri26m5F%2B%2B6gGPa%2Bv0Zzk%2BX3MgNFRMrz%2Fo60PYov6s555YVr3%2FqbriMQE8PgUd8dmUZGJ%2FDvW5HjWUrM866rMS%2Fa2pz7J%2F9yIRkPUSaZklGiUQIKVc4c0dKDRsWFI8JbvIqlFZZjovNZSUjsQ%2FeAfpb9KZPRWlPncifrHWxMCz0HS0mXrKNBBlg5X0kEYlK2gj2XoTrUxWSiqKmMn6ashGfkoRs5xhKERMJcPQh22JmJYcFUAt9VcLPA2duKEy1%2BuuO9NUC0DXhuaoTXGjb2dvEbuwDNle31eeXNFaEzjUb6k4lH4KNFmqAxSpwesIhtF%2Ba2s6TCFbX1HFwPc%2FMdOpW9f%2BWpEDJgRQRDK%2FIges%2FdyLkoBbOwPfV7mhm%2FqbKuL5lQjM9fhZE%2BwrzsArsd%2BWwNwveu%2BF7oGUh6nOgZTmOvT8xhfMxc4SIz7haQFYwrxtH0TREwrdsgMByy1trW5dCUvM1zbZRMRtU7e%2B2hbNVHvMMfOcLZIRMsty1UZzyVTyyKVhqfhok1ELBSyZa13promkg3sWwXiyaTpXMcr2hmliZTR9lOaShLTmlyQyFbCsC8Q1VXOVqitRDeVt43krHocygpQ4zK5A5AC39pJWzksN%2FXHHBXvHUB874an%2B9imfV1Jun4ZutLSBitZO5KG4IC6KQS%2FjohjoyeV%2Br8pFIV6%2BfeEuCtHNlMhEAiLe85P3UWczeFkuiiTytOTZqyQtwzTaeyNPHeUVwjmWW2A4tdlOgreWMKfCJyCmoTrVmwEZWAzER3TzY3%2BkQJ7pI9xGyakDViLdSrbE%2BPbT1c2UHDKYotnU6A92vah3W15nKy3iLLViE1V0a7dmKVBdF9C51o7kWtuD%2FeSlvL3obwv7qnfFxkwfw7yCs4zS2xaA%2B9c6iqeuN8fTeMbYGz8vVVaMwU9nHhaRaKky4LvL62vKoIpvPXDQcoV3tah6D6JpOI1RPPXFU3yqagnQXgAmWvXHxhuZlQr2m%2BP7SWFczFbz6I7ptrfsFFciqJadLvBw%2FCsR7NOoGKe%2B2ruqOmAWYLDlV5KM%2FCVqIzON6toF2rmRb3gi4kki6EajflY91Yav837IyvRYdGVo26922VnyGtr7Xu2y87Fb1kEEiT9DhOI0eAhWi9%2BRSw4gvvs%2F)

## **¿Cómo correr el proyecto?**

**Requerimentos** :
- [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/)
- [MinGW](https://www.mingw-w64.org/downloads/)

**Ejecutar en terminal** :

```
g++ -IC:\SFML-2.5.1\include\ -c main.cpp -o main.o
g++ -LC:\SFML-2.5.1\lib .\main.o -o main.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system
```
## **Referencias Bibliograficas**

- [Convert to SHA256 in C++ | Delft Stack](https://www.delftstack.com/howto/cpp/sha256-cpp/)
- [Blockchain Demo](https://andersbrownworth.com/blockchain/)
- [B+ Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html)
- [B+Tree Basics](https://www.youtube.com/watch?v=49P_GDeMDRo)
- [B+Tree Insertions](https://youtu.be/h6Mw7_S4ai0)
