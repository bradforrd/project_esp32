type Direction = 'forward' | 'backward' | 'right' | 'left';

const ESP32_IP = '192.168.4.1';

function App() {
  const moveButton = async (direction: Direction) => {
    try {
      await fetch(`http://${ESP32_IP}/move?dir=${direction}`, { method: 'GET' });
    } catch (err) {
      console.error('Nepodarilo sa nadviazat spojenie s ESP32', err);
    }
  };

  return (
    <>
      {/* Controls */}
      <div className='flex flex-col gap-5 outline outline-teal-500 rounded p-5 shadow-2xl'>
        <p className='text-teal-300 text-xl font-semibold uppercase text-center'>Controls</p>
        <div className='flex flex-col justify-center items-center gap-2'>
          <button className='bg-teal-500/50 text-teal-300 min-w-28 py-2 cursor-pointer hover:bg-teal-500/60 transition-all'
            onClick={() => moveButton('forward')}>
            FORWARD
          </button>
          <div className='flex gap-2'>
            <button className='bg-teal-500/50 text-teal-300 min-w-24 py-2 cursor-pointer hover:bg-teal-500/60 transition-all'
              onClick={() => moveButton('left')}>
              LEFT
            </button>
            <button className='bg-teal-500/50 text-teal-300 min-w-24 py-2 cursor-pointer hover:bg-teal-500/60 transition-all'
              onClick={() => moveButton('right')}>
              RIGHT
            </button>
          </div>
          <button className='bg-teal-500/50 text-teal-300 min-w-28 py-2 cursor-pointer hover:bg-teal-500/60 transition-all'
            onClick={() => moveButton('backward')}>
            BACKWARD
          </button>
        </div>
      </div>
    </>
  )
}

export default App