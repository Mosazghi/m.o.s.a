const canvas = document.getElementById('topdown');

canvas.addEventListener('click', (e) => {
  const x = e.clientX - canvas.offsetLeft;
  const y = e.clientY - canvas.offsetTop;
  document.getElementById('x').value = x;
  document.getElementById('y').value = y;
  console.log(`(${x}, ${y})`);
});

const buttons = document.getElementsByClassName('drop-button');
const test = document.getElementById('test');

for (let i = 0; i < buttons.length; i++) {
  buttons[i].addEventListener('click', () => {
    test.innerHTML = buttons[i].getAttribute('id');
  });
}

const liste = document.getElementById('liste').getElementsByTagName('tbody')[0];
const leggMerButton = document.getElementById('legg-mer-button');

leggMerButton.addEventListener('click', () => {
  let row = liste.insertRow();
  let kompNavn = row.insertCell(0);
  let ant = row.insertCell(1);

  kompNavn.innerHTML = document.getElementById('komponent').value;
  ant.innerHTML = document.getElementById('antall').value;
});

document.getElementById('bestill-button').addEventListener('click', sendData);

async function sendData() {
  const table = document.getElementById('liste');
  const formData = [];

  // Iterate over table rows (skipping the header row)
  for (let i = 1; i < table.rows.length; i++) {
    const row = table.rows[i];
    const rowData = {};

    // Iterate over table cells
    for (let j = 0; j < row.cells.length; j++) {
      const cell = row.cells[j];
      const columnName = table.rows[0].cells[j].innerText;
      const cellValue = cell.innerText;

      rowData[columnName] = cellValue;
    }

    formData.push(rowData);
  }
  console.log('form', JSON.stringify(formData));
  try {
    const res = await fetch('/dashboard', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(formData),
    });
    const data = await res.json();
    console.log('SENT: ', data);
  } catch (error) {
    console.error(error);
  }
  // const res = await fetch('/koordinater', {
  //   method: 'POST',
  //   headers: {
  //     'Content-Type': 'application/json',
  //   },
  //   body: JSON.stringify(formData),
  // })
  //   .then((response) => response.json())
  //   .then((data) => {
  //     console.log('data:', data);
  //     console.log('from:', formData);
  //   })
  //   .catch((err) => {
  //     console.error(err);
  //   });
}

// const form = document.querySelector('form');
// form.addEventListener('submit', async (e) => {
//   e.preventDefault(); // Hindrer siden i å refreshe når sumbit
//   // const formData = new FormData(form);

//   // const data = {
//   //   komponenter: formData.get(komponenter),
//   //   drop: formData.get('drop'),
//   // };

//   // if (x !== '' && y !== '') {
//   //   await fetch('http://localhost:4000/koordinater', {
//   //     method: 'POST',
//   //     body: JSON.stringify(data),
//   //     headers: {
//   //       'Content-type': 'application/json; charset=UTF-8',
//   //     },
//   //   });
//   // } else console.log('MÅ inneholde begge koordinater!');
// });
