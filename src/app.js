const path=require('path')
const express=require('express') //func that calls/loads express library 
const hbs=require('hbs')
const app=express()
const port=process.env.PORT || 3000

//Define Paths for express config
const publicDirectoryPath=path.join(__dirname, '../public')
const viewsPath=path.join(__dirname,'../templates/views')
const partialsPath=path.join(__dirname,'../templates/partials')

//Setup handlebars engine and views location
app.set('view engine','hbs')
app.set('views',viewsPath)
hbs.registerPartials(partialsPath)

app.use(express.static(publicDirectoryPath)) // used customise server

app.get('',(req, res)=>{
    res.render('index', {
        title: 'Smart Car Parking',
        name: 'Himanshi'
    }) //2nd arg is an obj that view can access
})

app.get('/about', (req, res)=>{
    res.render('about',{
        title: 'About Me',
        name:'Himanshi'
    })
})

app.get('/help', (rq, res)=>{
    res.render('help', {
        helpText: 'This site will help you check the parking spot availability. ',
        title:'Help',
        name:'Himanshi'
    })
})

app.get('/help/*', (req, res)=>{
    res.render('404page',{
        title:'404 Help',
        msg:'Help article not found.',
        name:'Himanshi'
    })
    })
    
    
    app.get('*', (req, res)=>{
    res.render('404page',{
        title:'404',
        msg: 'Page not found.',
        name:'Himanshi'
    })
    })

    app.listen(port, ()=>{
        console.log('Server is up on port '+port)
    })