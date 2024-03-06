type User = {
    /**
     * User id as defined by the database
    */
   user_id: number,
    /**
     * User's Username as entered when created
    */
    username: string,
}

type Convo = {
    /**
     * Convo id as defined by the database
    */
   convo_id: number,
    /**
     * Convo's name as entered when created
    */
    convo_name: string,
}

type Message = {
    /**
     * Message id as defined by the database
    */
   message_id: number,
    /**
     * Convo id as defined by the database
    */
    convo_id: number,
    /**
     * User id as defined by the database
    */
    user_id: number,
    /**
     * Timestamp of when the message was created
    */
    timestamp: string,
    /**
     * Message content as entered when created
    */
    content: string,
}