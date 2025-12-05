import { useEffect, useRef, useState, useCallback } from 'react';
import { Terminal } from 'xterm';
import { FitAddon } from 'xterm-addon-fit';
import { Unicode11Addon } from 'xterm-addon-unicode11';
import 'xterm/css/xterm.css';
import { Play, Square, RotateCcw } from 'lucide-react';

interface WebTerminalProps {
  projectSlug: string;
  projectName: string;
  onClose?: () => void;
}

export function WebTerminal({ projectSlug, projectName, onClose }: WebTerminalProps) {
  const terminalRef = useRef<HTMLDivElement>(null);
  const terminalInstance = useRef<Terminal | null>(null);
  const fitAddonRef = useRef<FitAddon | null>(null);
  const wsRef = useRef<WebSocket | null>(null);
  const [isRunning, setIsRunning] = useState(false);
  const [isConnected, setIsConnected] = useState(false);

  const writeWelcome = useCallback((term: Terminal) => {
    term.writeln('\x1b[1;34m╔════════════════════════════════════════════════╗\x1b[0m');
    term.writeln('\x1b[1;34m║\x1b[0m  \x1b[1;32mTerminal de Démo\x1b[0m - ' + projectName.substring(0, 25).padEnd(25) + '\x1b[1;34m║\x1b[0m');
    term.writeln('\x1b[1;34m╚════════════════════════════════════════════════╝\x1b[0m');
    term.writeln('');
    term.writeln('\x1b[90mCliquez sur "▶ Lancer" pour démarrer la démo.\x1b[0m');
    term.writeln('');
  }, [projectName]);

  useEffect(() => {
    if (terminalRef.current && !terminalInstance.current) {
      const term = new Terminal({
        cursorBlink: true,
        allowProposedApi: true,
        theme: {
          background: '#0f172a',
          foreground: '#e2e8f0',
          cursor: '#60a5fa',
          selectionBackground: '#334155',
          black: '#1e293b',
          red: '#ef4444',
          green: '#22c55e',
          yellow: '#eab308',
          blue: '#3b82f6',
          magenta: '#a855f7',
          cyan: '#06b6d4',
          white: '#f1f5f9',
        },
        fontFamily: '"Fira Code", Monaco, Menlo, "Ubuntu Mono", monospace',
        fontSize: 14,
        rows: 24,
        cols: 90,
        scrollback: 1000,
        convertEol: true,
      });

      const fitAddon = new FitAddon();
      fitAddonRef.current = fitAddon;
      term.loadAddon(fitAddon);
      
      // Charger l'addon Unicode11 pour gérer correctement les emojis et symboles
      const unicode11Addon = new Unicode11Addon();
      term.loadAddon(unicode11Addon);
      term.unicode.activeVersion = '11';
      
      term.open(terminalRef.current);
      
      setTimeout(() => fitAddon.fit(), 0);

      writeWelcome(term);
      terminalInstance.current = term;

      // Handle window resize
      const handleResize = () => {
        if (fitAddonRef.current) {
          fitAddonRef.current.fit();
        }
      };
      window.addEventListener('resize', handleResize);

      return () => {
        window.removeEventListener('resize', handleResize);
        if (wsRef.current) {
          wsRef.current.close();
        }
        term.dispose();
      };
    }
  }, [writeWelcome]);

  const startDemo = useCallback(() => {
    const term = terminalInstance.current;
    if (!term) return;

    setIsRunning(true);
    term.clear();
    term.writeln('\x1b[1;33m⏳ Connexion au serveur...\x1b[0m\n');

    // Fermer connexion existante
    if (wsRef.current) {
      wsRef.current.close();
    }

    try {
      // Construire l'URL WebSocket en fonction de l'hôte actuel
      const wsProtocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
      const wsUrl = `${wsProtocol}//localhost:5001/ws/terminal/${projectSlug}`;
      term.writeln(`\x1b[90mConnexion à ${wsUrl}...\x1b[0m\n`);
      
      const socket = new WebSocket(wsUrl);
      
      socket.onopen = () => {
        setIsConnected(true);
        term.writeln('\x1b[1;32m✓ Connecté!\x1b[0m\n');
      };

      socket.onmessage = (event) => {
        term.write(event.data);
      };

      socket.onclose = (event) => {
        setIsConnected(false);
        setIsRunning(false);
        term.writeln(`\n\x1b[90m--- Connexion fermée (code: ${event.code}) ---\x1b[0m`);
      };

      socket.onerror = (error) => {
        term.writeln('\x1b[1;31m✗ Erreur de connexion WebSocket\x1b[0m');
        term.writeln('\x1b[90mVérifiez que le backend Flask est lancé sur le port 5001\x1b[0m');
        console.error('WebSocket error:', error);
        setIsRunning(false);
        setIsConnected(false);
      };

      // Envoyer les entrées clavier
      term.onData((data) => {
        if (socket.readyState === WebSocket.OPEN) {
          socket.send(data);
        }
      });

      wsRef.current = socket;
    } catch (error) {
      term.writeln('\x1b[1;31m✗ Erreur: ' + error + '\x1b[0m');
      setIsRunning(false);
    }
  }, [projectSlug]);

  const stopDemo = useCallback(() => {
    if (wsRef.current) {
      wsRef.current.close();
      wsRef.current = null;
    }
    setIsRunning(false);
    setIsConnected(false);
    terminalInstance.current?.writeln('\n\x1b[1;33m⏹ Arrêté par l\'utilisateur\x1b[0m');
  }, []);

  const resetTerminal = useCallback(() => {
    const term = terminalInstance.current;
    if (term) {
      if (wsRef.current) {
        wsRef.current.close();
        wsRef.current = null;
      }
      setIsRunning(false);
      setIsConnected(false);
      term.clear();
      writeWelcome(term);
    }
  }, [writeWelcome]);

  return (
    <div className="bg-slate-900 rounded-xl border border-slate-700 overflow-hidden shadow-2xl">
      {/* Barre de titre style macOS */}
      <div className="flex items-center justify-between px-4 py-3 bg-slate-800 border-b border-slate-700">
        <div className="flex items-center gap-3">
          <div className="flex gap-2">
            <button 
              onClick={onClose}
              className="w-3 h-3 rounded-full bg-red-500 hover:bg-red-400 transition-colors"
              title="Fermer"
            />
            <div className="w-3 h-3 rounded-full bg-yellow-500" />
            <div className="w-3 h-3 rounded-full bg-green-500" />
          </div>
          <span className="text-sm text-slate-400 font-mono">
            ~/demo/{projectSlug}
          </span>
          {isConnected && (
            <span className="text-xs text-green-400 bg-green-900/30 px-2 py-0.5 rounded">
              ● Connecté
            </span>
          )}
        </div>
        
        {/* Boutons de contrôle */}
        <div className="flex gap-2">
          {!isRunning ? (
            <button
              onClick={startDemo}
              className="flex items-center gap-1.5 px-3 py-1.5 bg-green-600 hover:bg-green-500 text-white text-sm font-medium rounded-lg transition-colors"
            >
              <Play size={14} />
              Lancer
            </button>
          ) : (
            <button
              onClick={stopDemo}
              className="flex items-center gap-1.5 px-3 py-1.5 bg-red-600 hover:bg-red-500 text-white text-sm font-medium rounded-lg transition-colors"
            >
              <Square size={14} />
              Arrêter
            </button>
          )}
          <button
            onClick={resetTerminal}
            className="flex items-center gap-1.5 px-3 py-1.5 bg-slate-700 hover:bg-slate-600 text-slate-300 text-sm rounded-lg transition-colors"
            title="Réinitialiser"
          >
            <RotateCcw size={14} />
          </button>
        </div>
      </div>
      
      {/* Zone du terminal */}
      <div 
        ref={terminalRef} 
        className="p-2"
        style={{ minHeight: '400px' }}
      />
      
      {/* Barre d'info */}
      <div className="px-4 py-2 bg-slate-800/50 border-t border-slate-700 text-xs text-slate-500">
        <span>Interagissez avec le programme en tapant dans le terminal</span>
      </div>
    </div>
  );
}
