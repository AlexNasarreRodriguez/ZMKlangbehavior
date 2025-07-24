# Comportamiento de Cambio de Idioma (Language Toggle) para ZMK

Este módulo proporciona un comportamiento personalizado para ZMK que permite cambiar entre dos estados de idioma (por ejemplo, español e inglés) con una sola tecla. El estado del idioma se almacena en una variable global atómica, lo que permite que otros comportamientos personalizados puedan consultarla de forma segura y adaptar su funcionamiento.

## Características

- **Cambio de Idioma:** Asigna el comportamiento a una tecla en tu keymap para cambiar entre `LANG_FIRST` y `LANG_SECOND`.
- **Estado Global:** Expone una variable global `zmk_lang_state` y una función `zmk_lang_toggle_get_state()` para que otros módulos puedan leer el estado actual del idioma.
- **Fácil de Integrar:** Se integra como un módulo externo en tu configuración de firmware de ZMK.

## Cómo Usarlo

1.  **Añadir el módulo a tu firmware:**
    Asegúrate de que este módulo está incluido en la compilación de tu firmware ZMK. Normalmente, esto se hace añadiendo el repositorio a tu archivo `west.yml` y actualizando las dependencias con `west update`.

2.  **Habilitar el comportamiento:**
    Añade la siguiente línea a tu archivo de configuración `.conf` (por ejemplo, `corne.conf`):

    ```
    CONFIG_ZMK_BEHAVIOR_LANG_TOGGLE=y
    ```

3.  **Definir el comportamiento en tu keymap:**
    En tu archivo `.keymap`, primero define el comportamiento dándole un nombre:

    ```dts
    / {
        behaviors {
            lang_toggle: lang_toggle {
                compatible = "zmk,behavior-lang-toggle";
                #binding-cells = <0>;
            };
        };
    };
    ```

4.  **Asignar el comportamiento a una tecla:**
    Ahora puedes usar `&lang_toggle` en tus capas (layers) para asignarlo a la tecla que desees:

    ```dts
    keymap {
        compatible = "zmk,keymap";

        default_layer {
            bindings = <
                &kp Q  &kp W  &kp E  &kp R  &kp T     &kp Y  &kp U  &kp I  &kp O  &kp P
                &kp A  &kp S  &kp D  &kp F  &kp G     &kp H  &kp J  &kp K  &kp L  &kp SEMI
                &kp Z  &kp X  &kp C  &kp V  &kp B     &kp N  &kp M  &kp COMMA &kp DOT &lang_toggle
            >;
        };
    };
    ```

## Acceder al Estado del Idioma desde otros Comportamientos

Para que otros comportamientos reaccionen al cambio de idioma, puedes incluir el archivo de cabecera `behavior_lang_toggle.h` y llamar a la función `zmk_lang_toggle_get_state()`.

```c
#include "path/to/your/module/behaviors/behavior_lang_toggle.h"

void my_custom_function() {
    enum language current_lang = zmk_lang_toggle_get_state();

    if (current_lang == LANG_FIRST) {
        // Hacer algo para el primer idioma
    } else if (current_lang == LANG_SECOND) {
        // Hacer algo para el segundo idioma
    }
}
```
