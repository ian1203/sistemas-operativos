read -r MIN
sudo shutdown -h +"$MIN"
echo "Se apagará en $MIN minuto(s)."
sleep 10
sudo shutdown -c 2>/dev/null || true
sudo killall shutdown 2>/dev/null || true
echo "Timer cancelado."
read -r
