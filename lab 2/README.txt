Aplikacja minmax wykorzystuje bibliotekę statyczną, a aplikacja fib wykorzystuje bibliotekę dynamiczną.
Biblioteki statyczne dołączane są w trakcie linkowania, natomiast kod bibliotek dynamicznych udostępniany jest w trakcie wykonywania programu. 
Sprawia to, że aplikacje wykorzystujące biblioteki statyczne potrzebują przechowywać je w formacie półskompilowanym lokalnie.
Są one za to szybsze i niezależne od systemu. 
Aplikacje wykorzystujące biblioteki dynamiczne wystarczy, że podlinkują daną bibliotekę.
Dzięki temu można osiągnąć mniejszy rozmiar programu.
Oddzielenie biblioteki i programu sprawia, że aktualizacja biblioteki jest łatwiejsza (nie wymaga zmiany programu),
także daje to możliwość współdzielenia jednej biblioteki przez wiele programów.

Aby przetestować aplikacje, można uruchomić skrypt "start.sh", który wykonuje potrzebne kompilacje i konsolidacje.
Może wystąpić problem ze ścieżką do biblioteki dynamicznej.
Należy wtedy uruchomić ręcznie komendę:
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:."
w folderze gdzie znajduje się nasza biblioteka.