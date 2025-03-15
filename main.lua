local simpledraw = require"SimpleDraw"

function Draw(dt)
SimpleDraw.Clear(255,255,255)--Fondo Blanco
SimpleDraw.SetBrushColor(255,0,0)--Rojo
SimpleDraw.DrawCircle(400,300,50)
SimpleDraw.SetBrushColor(0,255,0)--Verde
SimpleDraw.DrawRect(200,200,100,100)
SimpleDraw.SetBrushColor(0,0,255)--Azul
SimpleDraw.DrawLine(100,100,700,500)
--SimpleDraw.SetBrushColor(255,255,0)
--SimpleDraw.DrawCircle(400 + math.sin(os.clock()) * 100,300,50)
end

webRequest("https://uselessfacts.jsph.pl/api/v2/facts/random")