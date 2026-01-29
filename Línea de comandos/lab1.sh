set -e
cd "$HOME"
NEWFOLDER="folder_nuevo_lab"
mkdir -p "$NEWFOLDER"
ls 
mv "$NEWFOLDER" "$HOME/Desktop/"
ls -d "$NEWFOLDER" 2>/dev/null || echo "El folder ya no está en $HOME"
cd "$HOME/Desktop"
ls 
rm -rf "$HOME/Desktop/$NEWFOLDER"
ls -d "$NEWFOLDER" 2>/dev/null || echo "El folder ha sido eliminado de $HOME/Desktop" 
ls
echo
read -r -p "Listo, presiona enter para salir..."
