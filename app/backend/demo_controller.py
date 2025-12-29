# Backend Flask pour contrôler la démo de SEvent

from flask import Flask, jsonify, send_from_directory
from flask_cors import CORS
import subprocess
import signal
import os
import psutil

app = Flask(__name__, static_folder='../dist')
CORS(app)

# Process pour SEvent
sevent_process = None
SEVENT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../projets/sevent-gestion-evenements'))
SEVENT_PORT = 5001

@app.route('/api/demo/sevent/start', methods=['POST'])
def start_sevent():
    global sevent_process
    
    try:
        # Vérifier si le processus est déjà en cours
        if sevent_process and sevent_process.poll() is None:
            return jsonify({'status': 'already_running', 'port': SEVENT_PORT})
        
        # Démarrer SEvent
        env = os.environ.copy()
        env['FLASK_APP'] = 'app.py'
        
        sevent_process = subprocess.Popen(
            ['python', 'app.py'],
            cwd=SEVENT_DIR,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            preexec_fn=os.setsid  # Pour pouvoir tuer tous les processus enfants
        )
        
        return jsonify({
            'status': 'started',
            'port': SEVENT_PORT,
            'pid': sevent_process.pid
        })
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500

@app.route('/api/demo/sevent/stop', methods=['POST'])
def stop_sevent():
    global sevent_process
    
    try:
        if sevent_process and sevent_process.poll() is None:
            # Tuer le groupe de processus
            os.killpg(os.getpgid(sevent_process.pid), signal.SIGTERM)
            sevent_process.wait(timeout=5)
            sevent_process = None
            return jsonify({'status': 'stopped'})
        else:
            return jsonify({'status': 'not_running'})
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500

@app.route('/api/demo/sevent/status', methods=['GET'])
def status_sevent():
    global sevent_process
    
    if sevent_process and sevent_process.poll() is None:
        return jsonify({
            'status': 'running',
            'port': SEVENT_PORT,
            'pid': sevent_process.pid
        })
    else:
        return jsonify({'status': 'stopped'})

# Servir l'application React
@app.route('/', defaults={'path': ''})
@app.route('/<path:path>')
def serve(path):
    if path != "" and os.path.exists(os.path.join(app.static_folder, path)):
        return send_from_directory(app.static_folder, path)
    else:
        return send_from_directory(app.static_folder, 'index.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
