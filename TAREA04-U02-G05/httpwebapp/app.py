#Webapp simple  de demostracion del protocolo http

#Librerias
from flask import Flask,render_template,request
from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired
import datetime

#Configuracion del servidor flask
app = Flask(__name__)
app.config['SECRET_KEY'] ="159753"

#Clase de formulario donde guardamos la informacion 
class UsuarioForm(FlaskForm):
    nombre = StringField("Nombre: ",validators= [DataRequired()])
    apellido = StringField("Apellido: ",validators=[DataRequired()])
    numeroCedula = StringField("Numero de Cedula: ",validators=[DataRequired()])
    correo = StringField("Correo: ",validators=[DataRequired()])
    contraseña = StringField("Contraseña", validators=[DataRequired()])
    submit = SubmitField("Registrar")


#Pagina principal del formulario
@app.route("/",methods =["GET","POST"])
def index():

    nombre = None
    form = UsuarioForm()
    
    if form.validate_on_submit():
        # Fecha y hora actual
        now = datetime.datetime.now()
        timestamp = now.strftime("%Y%m%d_%H%M%S")
        
        #Crear un JSOM de nuestra clase formulario
        form_data = {
            "nombre": form.nombre.data,
            "apellido": form.apellido.data,
            "numeroCedula": form.numeroCedula.data,
            "correo": form.correo.data,
            "contraseña": form.contraseña.data
        }
        
        
        #Guardar el JSON en un archvo txt para verificar que llegan los datos
        form_string = str(form_data)
        with open(f"{timestamp}.txt", "w") as f:
            f.write(form_string)
        
        #Vaciar el formulario
        form.nombre.data = ""
        form.apellido.data = ""
        form.numeroCedula.data = ""
        form.correo.data = ""
        form.contraseña.data = ""
     
    #Renderizado de la pagina web   
    return render_template("index.html", nombre=nombre, form=form)

#Configuraciones del servidor de desarrolo de flask
#host = '0.0.0.0' es para que aparezca en la red local 
#con la ip del equipo, si no solo aparece en 127.0.0.1
#y no se ve en otras compus en la red local

#Tambien hay que permitir en puerto 5000 en en firewall
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)
    
