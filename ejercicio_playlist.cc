#include <iostream>
#include <string>
#include <vector>

struct Cancion {
    std::string titulo;
    std::string artista;
    int duracion_segundos;
    int reproducciones;
    bool favorita;
};

// Declaración de funciones
void ConsultarPlaylist(const std::vector<Cancion>& playlist);
void ReproducirCancion(std::vector<Cancion>& playlist);
void CambiarEstadoFavorita(std::vector<Cancion>& playlist);
void ConsultarFavoritas(const std::vector<Cancion>& playlist);
void MostrarEstadisticasGenerales(const std::vector<Cancion>& playlist);

int main() {
    // Playlist inicial con datos predeterminados
    std::vector<Cancion> playlist = {
        {"Bohemian Rhapsody", "Queen", 354, 120, true},
        {"Hotel California", "Eagles", 391, 85, false},
        {"Blinding Lights", "The Weeknd", 200, 210, true},
        {"Shape of You", "Ed Sheeran", 233, 175, false},
        {"Take On Me", "a-ha", 225, 95, true}
    };

    int opcion = 0;

    do {
        std::cout << "\n=========================================\n";
        std::cout << "        ADMINISTRADOR DE PLAYLIST        \n";
        std::cout << "=========================================\n";
        std::cout << "1. Consultar lista completa de canciones\n";
        std::cout << "2. Reproducir una cancion\n";
        std::cout << "3. Marcar/Desmarcar cancion como favorita\n";
        std::cout << "4. Ver canciones favoritas\n";
        std::cout << "5. Ver estadisticas generales de la playlist\n";
        std::cout << "6. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ConsultarPlaylist(playlist);
                break;
            case 2:
                ReproducirCancion(playlist);
                break;
            case 3:
                CambiarEstadoFavorita(playlist);
                break;
            case 4:
                ConsultarFavoritas(playlist);
                break;
            case 5:
                MostrarEstadisticasGenerales(playlist);
                break;
            case 6:
                std::cout << "\nCerrando reproductor de musica...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}

// 1. Muestra todas las canciones en la playlist
void ConsultarPlaylist(const std::vector<Cancion>& playlist) {
    if (playlist.empty()) {
        std::cout << "\nLa playlist esta vacia.\n";
        return;
    }

    std::cout << "\n--- CANCIONES EN LA PLAYLIST ---\n";
    for (size_t i = 0; i < playlist.size(); ++i) {
        int min = playlist[i].duracion_segundos / 60;
        int seg = playlist[i].duracion_segundos % 60;

        std::cout << (i + 1) << ". " << playlist[i].titulo << " - " << playlist[i].artista
                << " [" << min << ":" << (seg < 10 ? "0" : "") << seg << "]"
                << " | Reps: " << playlist[i].reproducciones
                << " | " << (playlist[i].favorita ? "[FAVORITA]" : "") << "\n";
    }
}

// 2. Incrementa el contador de reproducciones de una canción
void ReproducirCancion(std::vector<Cancion>& playlist) {
    ConsultarPlaylist(playlist);

    int seleccion = 0;
    std::cout << "\nSeleccione el numero de la cancion a reproducir: ";
    std::cin >> seleccion;

    if (seleccion < 1 || seleccion > static_cast<int>(playlist.size())) {
        std::cout << "ERROR: La cancion seleccionada no existe.\n";
        return;
    }

    Cancion& c = playlist[seleccion - 1];
    c.reproducciones++;

    std::cout << "\nReproduciendo ahora: '" << c.titulo << "' de " << c.artista << "...\n";
    std::cout << "Total de reproducciones de esta cancion: " << c.reproducciones << "\n";
}

// 3. Alterna o cambia el estado de favorita (true/false)
void CambiarEstadoFavorita(std::vector<Cancion>& playlist) {
    ConsultarPlaylist(playlist);

    int seleccion = 0;
    std::cout << "\nSeleccione el numero de la cancion para cambiar su estado de favorita: ";
    std::cin >> seleccion;

    if (seleccion < 1 || seleccion > static_cast<int>(playlist.size())) {
        std::cout << "ERROR: La cancion seleccionada no existe.\n";
        return;
    }

    Cancion& c = playlist[seleccion - 1];
    c.favorita = !c.favorita; // Invierte el estado actual

    std::cout << "La cancion '" << c.titulo << "' ahora " 
            << (c.favorita ? "es FAVORITA." : "ya NO es favorita.") << "\n";
}

// 4. Muestra únicamente las canciones marcadas como favoritas
void ConsultarFavoritas(const std::vector<Cancion>& playlist) {
    std::cout << "\n--- CANCIONES FAVORITAS ---\n";
    bool hay_favoritas = false;

    for (size_t i = 0; i < playlist.size(); ++i) {
        if (playlist[i].favorita) {
            hay_favoritas = true;
            int min = playlist[i].duracion_segundos / 60;
            int seg = playlist[i].duracion_segundos % 60;

            std::cout << "- " << playlist[i].titulo << " - " << playlist[i].artista
                    << " [" << min << ":" << (seg < 10 ? "0" : "") << seg << "]"
                    << " | Reps: " << playlist[i].reproducciones << "\n";
        }
    }

    if (!hay_favoritas) {
        std::cout << "No tienes canciones marcadas como favoritas aun.\n";
    }
}

// 5. Muestra métricas completas (canción más reproducida, duración total, etc.)
void MostrarEstadisticasGenerales(const std::vector<Cancion>& playlist) {
    if (playlist.empty()) {
        std::cout << "\nNo hay datos para mostrar. La playlist esta vacia.\n";
        return;
    }

    int total_canciones = static_cast<int>(playlist.size());
    int cantidad_favoritas = 0;
    int total_reproducciones = 0;
    int duracion_total_segundos = 0;

    int max_reproducciones = -1;
    std::string mas_reproducida_titulo = "";
    std::string mas_reproducida_artista = "";

    for (const auto& c : playlist) {
        duracion_total_segundos += c.duracion_segundos;
        total_reproducciones += c.reproducciones;

        if (c.favorita) {
            cantidad_favoritas++;
        }

        if (c.reproducciones > max_reproducciones) {
            max_reproducciones = c.reproducciones;
            mas_reproducida_titulo = c.titulo;
            mas_reproducida_artista = c.artista;
        }
    }

    // Formato de tiempo para la duración total (Horas, Minutos, Segundos)
    int horas = duracion_total_segundos / 3600;
    int minutos = (duracion_total_segundos % 3600) / 60;
    int segundos = duracion_total_segundos % 60;

    std::cout << "\n=========================================\n";
    std::cout << "       ESTADISTICAS DE LA PLAYLIST       \n";
    std::cout << "=========================================\n";
    std::cout << "Numero total de canciones: " << total_canciones << "\n";
    std::cout << "Cantidad de canciones favoritas: " << cantidad_favoritas << "\n";
    std::cout << "Total acumulado reproducciones: " << total_reproducciones << "\n";
    std::cout << "Duracion total de la playlist: ";
    
    if (horas > 0) std::cout << horas << "h ";
    std::cout << minutos << "m " << segundos << "s\n";

    if (max_reproducciones > 0) {
        std::cout << "Cancion mas reproducida: " << mas_reproducida_titulo 
                << "' de " << mas_reproducida_artista 
                << " (" << max_reproducciones << " reproducciones)\n";
    } else {
        std::cout << "Aun no se ha reproducido ninguna cancion\n";
    }
    std::cout << "=========================================\n";
}

/*4. Administrador de playlist
Una aplicación musical necesita administrar una playlist creada por el usuario. Cada
canción posee un título, artista, duración en segundos, número de reproducciones y un
indicador que determina si ha sido marcada como favorita.
El programa debe permitir reproducir una canción, incrementando su contador de
reproducciones, así como marcar o desmarcar canciones como favoritas.
El usuario podrá consultar las canciones favoritas, conocer cuál ha sido la canción
más reproducida y obtener la duración total de la playlist.
Además, el sistema deberá mostrar estadísticas generales de la playlist, como número
de canciones, cantidad de canciones favoritas y total acumulado de reproducciones.*/