[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8843467&assignment_repo_type=AssignmentRepo)

# Block.h
## Librerias
1. **ctime**: Contiene definiciones para obtener y manipular información de fecha y hora.
2. **sstream**: Proporciona clases de flujo de cadenas.
3. **SHA256.h**: Implementación de la función SHA256

## Implementación de Block
Es un objeto de **clase final**, esto significa que la clase amiga BLockchain no se puede anular en una clase derivada o que no se puede derivar una clase.

### Atributos privados:
1. **m_index**: Tipo numérico sin signo que garantiza 32 bits y representa el index.
2. **m_nonce**: Tipo entero con signo con 64 bits y representa al número o valor que solo se puede usar una vez.
3. **m_data**: Tipo string que representa la data.
4. **m_hash**: Tipo string que representa el hash.
5. **m_time**: Tipo integral que contiene el número de segundos.

### Funciones privadas:
1. **CalculateHash**: Retorna un tipo string que calcula el hash.

### Atributos públicos:
1. **PrevHash**: Tipo string que representa el hash previo al bloque.
2. **GetIndex**: Retorna el index.
3. **GetData**: Retorna la data.
4. **GetTime**: Retorna el tiempo actual.
5. **GetHash**: Retorna el hash.

### Funciones públicas:
1. **Block**: Constructor que inicializa el m_nonce en -1 y m_time con la hora actual.
2. **BLock(indexInput,dataInput)**: Constructor con paramatros que inicializan a m_index, m_data y además m_nonce en -1 y m_time con la hora actual. 
3. **SetAsGenesis**: Setea el primer bloque del blockchain.
4. **DOMine**: Mina el bloque. 