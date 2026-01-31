import { useState } from 'react';

function App() {
  const [count, setCount] = useState(0)

  return (
    <>
      <p className='text-emerald-500'>Current count: <span className='font-medium'>{count}</span></p>
      <button onClick={() => setCount(count => count + 1)}>Click me!</button>
    </>
  )
}

export default App
