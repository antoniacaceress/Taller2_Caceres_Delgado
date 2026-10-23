# Taller 2 – Hospital Marmaja: Clasificación y AVL

Estructura de Datos · II Semestre 2026

Programa de consola en C++ que extiende el Taller 1. Los pacientes se leen desde un archivo de
texto y entran a una cola. Al atenderlos, salen de la cola en el mismo orden en que llegaron, un
árbol de decisión determina el servicio que les corresponde según sus características y se
guardan en el árbol AVL de ese servicio.

La cola, el árbol de decisión y los árboles AVL están hechos a mano con nodos y punteros, sin usar
contenedores de la STL.

## Integrantes

Antonia Cáceres, RUT 22.050.742-4, usuario de GitHub antoniacaceress, carrera ICCI, paralelo ‹completar›.

Benjamin Delgado, RUT 22.223.703-3, usuario de GitHub zomvr2, carrera ICCI, paralelo ‹completar›.

## Compilar

Hace falta un compilador con C++14. Desde la carpeta raíz del repositorio:

```
g++ -std=c++14 -Wall Taller2/*.cpp -o hospital
```

O con CMake:

```
cmake -S . -B build
cmake --build build
```

## Ejecutar

El programa lee los pacientes desde `Prueba.txt`, que debe estar en la carpeta desde la
que se ejecuta:

```
./hospital
```

Si se compiló con CMake el ejecutable queda en `build/` y `Prueba.txt` se copia ahí
automáticamente. En Windows termina en `.exe`.

## Archivo de entrada

Una línea por paciente, con los campos separados por `;`:

```
ID;Nombre;Edad;Temperatura;PresionArterial;Dolor;TipoDolor;Trauma;SintomasNeurologicos;RequiereCirugia;DiasHospitalizacion
```

Por ejemplo:

```
001;Juan Perez;25;37.0;120;3;otro;0;0;0;0
002;Maria Soto;67;36.5;140;6;pecho;0;0;0;0
```

| Campo | Valores aceptados |
|---|---|
| ID | Exactamente 3 dígitos (`001` a `999`), no repetido. Es la clave del AVL y con largo fijo la comparación de texto ordena igual que la numérica |
| Nombre | No vacío |
| Edad | Entero entre 0 y 120 |
| Temperatura | Decimal entre 30 y 45 (°C) |
| PresionArterial | Entero entre 0 y 300 (presión sistólica en mmHg) |
| Dolor | Entero entre 0 y 10 |
| TipoDolor | `pecho`, `cabeza`, `abdomen`, `extremidad` u `otro` (sin importar mayúsculas) |
| Trauma, SintomasNeurologicos, RequiereCirugia | `0` o `1` |
| DiasHospitalizacion | Entero entre 0 y 365 |

Las líneas con formato inválido, valores fuera de rango o IDs repetidos se ignoran y se
informan por pantalla.

## Árbol de decisión

‹Completar: dibujo del árbol y justificación de cada pregunta.›

Empates: en las comparaciones con `>=` el valor límite cuenta como "sí". Un paciente con
temperatura exactamente 38.5 o dolor exactamente 8 va a Urgencias, y uno con exactamente
2 días de hospitalización va a Hospitalización. Un paciente con exactamente 14 años ya no va a
Pediatría (`Edad < 14`).

Datos inválidos: los pacientes con campos fuera de rango se descartan al leer el archivo
(ver tabla anterior), así que al árbol solo llegan pacientes válidos. Si aun así el árbol no
pudiera asignar un servicio, el paciente se informa por pantalla y se descarta.

El menú tiene la opción `5. Ver arbol de decision` para mostrar el árbol en preorden, inorden
o postorden.
