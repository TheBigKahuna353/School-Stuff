import axios from 'axios';
import React from "react";
import CSS from 'csstype';
import { Paper, AlertTitle, Alert, Snackbar } from "@mui/material";
import UserListObject from "./UserListObject";
import { useUserStore } from '../store';


const UserList = () => {
    
    const users = useUserStore(state => state.users)
    const setUsers = useUserStore(state => state.setUsers)

    const [errorFlag, setErrorFlag] = React.useState(false)
    const [errorMessage, setErrorMessage] = React.useState("")
    React.useEffect(() => {
        const getUsers = () => {
            axios.get('http://localhost:3000/api/users')
                .then((response) => {
                     setErrorFlag(false)
                    setErrorMessage("")
                    setUsers(response.data)
                }, (error) => {
                    setErrorFlag(true)
                    setErrorMessage(error.toString() + " defaulting to old users changes app may not work as expected")
                })
        }
    getUsers()
    }, [setUsers])

    // snack bar
    const [snackOpen, setSnackOpen] = React.useState(false)
    const [snackMessage, setSnackMessage] = React.useState("")
    const handleSnackClose = (event?: React.SyntheticEvent | Event, reason?: string) => {
        if (reason === 'clickaway') {
            return;
        }
        setSnackOpen(false);
    };

    const handleSnackOpen = (message: string) => {
        setSnackMessage(message)
        setSnackOpen(true)
    }

    const user_rows = () => users.map((user: User) => <UserListObject key={ user.user_id + user.username } user={user} snack={handleSnackOpen}/>)

    const card: CSS.Properties = {
        padding: "10px",
        margin: "20px",
        display: "block",
        width: "fit-content"
    }


    return (
        <div>
            <Paper elevation={3} style={card} >
                <h1>UserList </h1>
                <div style={{ display: "inline-block", maxWidth: "965px", minWidth: "320" }}>
                    {errorFlag?
                    <Alert severity = "error">
                        <AlertTitle> Error </AlertTitle>
                        { errorMessage }
                    </Alert>: ""}
                    { user_rows() }
                </div>
            </Paper>
            <Snackbar
                autoHideDuration={6000}
                open={snackOpen}
                onClose={handleSnackClose}
                key={snackMessage}
                >
                <Alert onClose={handleSnackClose} severity="success" sx={{
                    width: '100%'
                }}>
                    {snackMessage}
                </Alert>
            </Snackbar>
        </div>
    )
}
export default UserList;